function [camImg screenImg] = grabScreenshotAndCamerashot()
system('del cameraShot.jpg');
system('del screenshot.bmp');
textFile = fopen('imageGrabber.txt', 'w');
fprintf(textFile, '%i',1);
fclose(textFile);
while ~exist('cameraShot.jpg') 
end
pause(1.0);
camImg = imread('cameraShot.jpg');
while ~exist('screenshot.bmp') 
end
pause(1.0);
screenImg = im2double((imread('screenshot.bmp')));
end