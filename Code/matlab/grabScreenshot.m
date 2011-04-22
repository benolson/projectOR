function img = grabScreenshot()
system('screenshot.exe');
img = imread('screen.bmp');
end