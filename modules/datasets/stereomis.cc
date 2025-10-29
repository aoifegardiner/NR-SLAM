/*
 * This file is part of NR-SLAM
 *
 * Copyright (C) 2022-2023 Juan J. Gómez Rodríguez, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
 *
 * NR-SLAM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stereomis.h"

#include <fstream>
#include <sys/stat.h>

#include <boost/filesystem.hpp>

#include "absl/log/log.h"

using namespace std;

Stereomis::Stereomis(const std::string &video_path, const std::string& other_video_path) {
    string path = video_path.substr(0,video_path.find_last_of("/"));
    string images_dir = path + "/left";

    //Check if the video has been already split into single frames
    struct stat buffer;
    if(stat(images_dir.c_str(),&buffer) != 0){   //Not processed
        LOG(INFO) << "Splitting video into frames...";

        SplitVideoIntoFrames(path, video_path, other_video_path);
    }
    else{   //Already processed, just read images names
        LOG(INFO) << "Loading already split dataset";

        ifstream names_file_reader;
        names_file_reader.open(path + "/namesLeft.txt");

        if(!names_file_reader.is_open()){
            LOG(ERROR) << "Could not open names file at: " << path + "/names.txt";
            return;
        }

        left_images_names_.clear();

        while(!names_file_reader.eof()){
            string image_name;
            getline(names_file_reader, image_name);
            left_images_names_.push_back(image_name);
        }

        names_file_reader.close();

        ifstream right_names_file_reader;
        right_names_file_reader.open(path + "/namesRight.txt");

        if(!right_names_file_reader.is_open()){
            LOG(ERROR) << "Could not open names file at: " << path + "/names.txt";
            return;
        }

        right_images_names.clear();

        while(!right_names_file_reader.eof()){
            string image_name;
            getline(right_names_file_reader, image_name);
            right_images_names.push_back(image_name);
        }

        right_names_file_reader.close();

    }
}

absl::StatusOr<cv::Mat> Stereomis::GetImage(const int idx) {
    if(idx >= left_images_names_.size()) {
        return absl::InternalError("Image index out boundaries.");
    }

    return cv::imread(left_images_names_[idx], cv::IMREAD_UNCHANGED);
}

absl::StatusOr<cv::Mat> Stereomis::GetRightImage(const int idx) {
    if(idx >= right_images_names.size()) {
        return absl::InternalError("Image index out boundaries.");
    }

    return cv::imread(right_images_names[idx], cv::IMREAD_UNCHANGED);
}

bool Stereomis::SplitVideoIntoFrames(const std::string &path, const std::string &video_path,
                                  const std::string& other_video_path) {
    const bool has_two_videos = !other_video_path.empty();

    // Open video.
    cv::VideoCapture video_capture(video_path);

    if (!video_capture.isOpened()){
        LOG(FATAL) << "Could not open video at: " << video_path;
        return false;
    }

    const int n_frames = video_capture.get(cv::CAP_PROP_FRAME_COUNT);

    // Open other video if it exists.
    cv::VideoCapture other_video_capture;
    if (has_two_videos) {
        other_video_capture = cv::VideoCapture(other_video_path);

        if (!other_video_capture.isOpened()) {
            LOG(FATAL) << "Could not open video at: " << other_video_path;
            return false;
        }
    }

    // Open file to save name files.
    ofstream left_names_writer, right_names_writer;
    left_names_writer.open(path + "/namesLeft.txt");
    right_names_writer.open(path + "/namesRight.txt");
    if(!left_names_writer.is_open()){
        LOG(FATAL) << "Could not create names file at: " << path + "/names.txt";
        return false;
    }

    // Create output directory.
    const string left_images_path(path + "/left");
    if(!boost::filesystem::create_directory(left_images_path)){
        LOG(FATAL) << "Could not create output directory at: " << left_images_path;
        return false;
    }

    const string right_images_path(path + "/right");
    if(!boost::filesystem::create_directory(right_images_path)){
        LOG(FATAL) << "Could not create output directory at: " << right_images_path;
        return false;
    }

    int idx = 0;

    left_images_names_.clear();
    right_images_names.clear();

    // Use this for StereoMIS 01.01.
    leftCal_ = (cv::Mat_<double>(3,3) << 1033.894287109375, 0.0, 604.578857421875,
            0.0, 1033.7147216796875, 514.9761962890625,
            0.0, 0.0, 1.0);

    leftDistorsion_ = (cv::Mat_<double>(1,5) << -0.00020782629144378006, 0.00018025403551291674, 0.0, 0.0, 9.6945594123099e-05);
    
    rightCal_ = (cv::Mat_<double>(3,3) << 1034.3970947265625, 0.0, 695.969970703125,
            0.0, 1034.196533203125, 514.6074829101562,
            0.0, 0.0, 1.0);
    rightDistorsion_ = (cv::Mat_<double>(1,5) << 0.0011366507969796658, -0.005894931964576244, 0.0, 0.0, 0.005956979002803564);

    R = (cv::Mat_<double>(3,3) << 9.99999991e-01,  3.64895316e-05, -1.29972150e-04,
          -3.64927614e-05,  9.99999999e-01, -2.48481197e-05,
          1.29971243e-04,  2.48528625e-05,  9.99999991e-01);
    t = (cv::Mat_<double>(3,1) << -4.159885406494141,
            0.018231099471449852,
            0.02658929117023945);

    cv::Size leftImSize(1024.0,1280.0);

    cv::Size newSize = cv::Size(leftImSize.width,leftImSize.height);

    cv::stereoRectify(leftCal_, leftDistorsion_, rightCal_, rightDistorsion_, leftImSize, R, t, R_l, R_r, P_l, P_r, Q, cv::CALIB_ZERO_DISPARITY, -1, newSize, 0, 0);
    cv::initUndistortRectifyMap(leftCal_, leftDistorsion_, R_l, P_l.rowRange(0, 3).colRange(0, 3),
                                newSize, CV_32F, M1l, M2l);
    cv::initUndistortRectifyMap(rightCal_, rightDistorsion_, R_r, P_r.rowRange(0, 3).colRange(0, 3),
                                newSize, CV_32F, M1r, M2r);

    LOG(INFO) << "P_l: " << P_l;
    LOG(INFO) << "P_r: " << P_r;

    while(true){
        cv::Mat left_image, right_image;
        if(!has_two_videos) {
            cv::Mat image;
            video_capture >> image;

            if (image.empty())
                break;

            int rows = image.rows;
            int cols = image.cols;
            int half_height = rows / 2;
            cv::Rect left_ROI(0, 0, cols, half_height);
            cv::Rect right_ROI(0, half_height, cols, half_height);
            left_image = image(left_ROI);
            right_image = image(right_ROI);
        } else {
            video_capture >> left_image;
            other_video_capture >> right_image;

            if (left_image.empty() || right_image.empty())
                break;
        }

        // Rectify images.
        cv::Mat left_image_rectified, right_image_rectified;
        cv::remap(left_image, left_image_rectified, M1l, M2l, cv::INTER_LINEAR);
        cv::remap(right_image, right_image_rectified, M1r, M2r, cv::INTER_LINEAR);

        // Save images.
        const string left_image_name = left_images_path + "/" + to_string(idx) + ".png";
        cv::imwrite(left_image_name, left_image_rectified);

        left_names_writer << left_image_name << endl;
        left_images_names_.push_back(left_image_name);

        const string right_image_name = right_images_path + "/" + to_string(idx) + ".png";
        cv::imwrite(right_image_name, right_image_rectified);

        right_names_writer << right_image_name << endl;
        right_images_names.push_back(right_image_name);

        idx++;
        LOG(INFO) << "Processed image " << idx << " of " << n_frames;
    }

    return true;
}
