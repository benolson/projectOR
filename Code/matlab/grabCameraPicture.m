function [camImg screenImg] = grabScreenshotAndCamerashot()
textFile = fopen('imageGrabber.txt', 'w');
fprintf(textxfile, '%i',1);
img = imread('cameraShot.jpg');
cameraImage = im2double((imread('screenshot.jpg')));
end