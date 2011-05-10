function [camImg screenImg] = grabImages()
system('del cameraShot.jpg');
system('del screenshot.bmp');
fprintf('files deleted! file exists: %d\n',exist('cameraShot.jpg'));

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