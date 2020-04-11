#include "opencv2/opencv.hpp"
#include <bits/stdc++.h>
#include <cstdio>
#include <ctime>
using namespace std;
using namespace cv;
int tasks();
void uploadVideo();
void display();
void playVideo();
void login();
int main()
{
    login();
    return 0;
}
void login()
{
    //Task (a) ------------------A simple login feature which take username as input------------------------------------------------
    cout<<"*********Welcome in the program************"<<endl;
    cout<<"--> Enter username to login into editor --"<<endl;
    cout<<"Username: ";
    string username;
    cin>>username;
    cout<<"Welcome --> "<<username<<" <--You can do following operations here -"<<endl;
    cout<<endl;
    tasks();
}
int tasks()
{
    cout<<"--> Enter specific key to perform that task"<<endl;
    cout<<"** Enter (1) upload video using webcam (Red channel will be extracted and gausian blur will be applied to video )"<<endl;
    cout<<"** Enter (2) to display all videos recorded"<<endl;
    cout<<"** Enter (3) to play a specific video"<<endl;
    cout<<"** Any other key to logout"<<endl;
    int option;
    cin>>option;
    if(option==1)
        uploadVideo();
    else if(option==2)
        display();  
    else if(option==3)
        playVideo();
    else if(option>=4)
        exit(0);
    tasks();
}
void uploadVideo()
{
    //Task (b) -----------------------To record a video using webcam----------------------------------
    cout<<"Enter the name for the video file (without extension and spaces)"<<endl;
    string fileName;
    cin>>fileName;
    VideoCapture cap(0); 
    if(!cap.isOpened())
    {
        cout << "Error opening video stream" << endl; 
        return;
    }
    //Task (e) ------------------ TO store video in disk the filename is taken as input ---------------------- 
    string path="videofile/";
    path+=fileName;
    path+=".avi";
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);  
    clock_t start;
    double duration;
    VideoWriter video(path,CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height)); 
    int fg=0;
    while(1)
    {
        if(fg==0)
        {
            start = clock();
        }
        //--------------Implementation of time limit of 10 seconds---------------------
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        if(duration>=10)
            break;
        Mat frame; 
        cap >> frame;
        if (frame.empty())
            break;
        imshow("Frame", frame);

        //Task (c)----------------Extracting Red channels from the frame-----------------------------
        Mat planes[3],fin_img,g;
        split(frame,planes);
        vector<Mat>channels;
        g= Mat::zeros(Size(frame_width, frame_height), CV_8UC1);
        channels.push_back(planes[0]);
        channels.push_back(g);
        channels.push_back(g);  
        merge(channels, fin_img);
        //--------------------------Red channels Extracted-------------------------

        //Task (d)----------------To apply gausian filter(blur) in the frames---------------------
        Mat frame_blurred_with_5x5_kernel;
        GaussianBlur(fin_img, frame_blurred_with_5x5_kernel, Size(5, 5), 0);
        video.write(frame_blurred_with_5x5_kernel);   
        fg=1;
        char c = (char)waitKey(1);
        if( c == 27 ) 
        break;

    }
    cap.release();
    video.release();
    destroyAllWindows();
}
void display()
{
    //Task (f) --------------TO show the list of videos recorded in such a way--------------------
    vector<cv::String> fn;
    string path = "videofile";
    cv::glob(path,fn,false);
    cout<<"---- Here is the list of all recorded videos ----"<<endl;
    for(int i=0;i<fn.size();i++)
    {
        cout<<i+1<<"-> ";
        for(int j=10;j<fn[i].size();j++)
            cout<<fn[i][j];
        cout<<endl;
    }
    return ;
}
void playVideo()
{

    //To play the video by selecting a specific filename
    cout<<"Enter the name of the video file to play(with extension) "<<endl;
    string fileName;
    cin>>fileName;
    string path="videofile/";
    path+=fileName;
    VideoCapture cap(path);
    if ( !cap.isOpened() )
    {
        cout << "Error --> Incorrect filename or Cannot open the video file. \n";
        return ;
    }
    double fps = cap.get(CV_CAP_PROP_FPS);
    namedWindow("Media Player",CV_WINDOW_AUTOSIZE);
    while(1)
    {
        Mat frame;
        if (!cap.read(frame))
        {
            break;
        }
        imshow("Media_Player", frame);
        if(waitKey(30) == 27)
        { 
            break; 
        }
    }
    cap.release();
    destroyAllWindows();
    return ;
}
