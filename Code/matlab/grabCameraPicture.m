function img = takePicture()
system('takePicture.exe');
img = imread('screenshot.jpg');
end