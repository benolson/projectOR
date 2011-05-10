%------------------------------
% Gaussian Pyramid
% by Marco Zennaro
% http://www.zennaro.net
%------------------------------

%-------------------------------------------
function [RI] = gaussianPiramid(imageToReduce)

gaussianFilter = fspecial('gaussian', [3 3], 0.5);

while 1
   imageSize = size(imageToReduce);
   minImageSize = min(imageSize(0), imageSize(1));
   if (minImageSize < 32)
       break;
   end
   imageToReduce = 
end