function cameraImage = takePicture()
system('takePicture.exe');
cameraImage = im2double((imread('screenshot.jpg')));
end