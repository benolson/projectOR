% cal1 = imread('cal1.png');
% cal2 = imread('cal2.png');
% fullscreen(cal2,2)
% camImage = takePicture();
% fullscreen(cal1,2)
% camImageBlack = takePicture();

%imshow(camImage-camImageBlack);
diff = camImage - camImageBlack;

h = fspecial('gaussian',10,10);
diff=imfilter(diff,h);

rdiff = diff(:,:,1);
gdiff = diff(:,:,2);
bdiff = diff(:,:,3);

meandiff = mean(diff,3);

[dummy, rmax] = max(rdiff(:) - meandiff(:));
[dummy, gmax] = max(gdiff(:) - meandiff(:));
[dummy, bmax] = max(bdiff(:) - meandiff(:));
[dummy, wmax] = max(meandiff(:));
newImage = meandiff;
newImage(rmax) = 255;
newImage(gmax) = 255;
newImage(bmax) = 255;
newImage(wmax) = 255;

imshow(newImage);
figure;
[rmax_x rmax_y] = ind2sub(size(diff),rmax);
[gmax_x gmax_y] = ind2sub(size(diff),gmax);
[bmax_x bmax_y] = ind2sub(size(diff),bmax);
[wmax_x wmax_y] = ind2sub(size(diff),wmax);
for i=1:1
    inpoints = [rmax_x rmax_y; gmax_x gmax_y; bmax_x bmax_y; wmax_x wmax_y];
    c = i
    
    basepoints = c*[0 0; 0 1280; 800 1280; 800 0];

    tform = findHomography(inpoints,basepoints);
    dogImage = imread('im.jpg');
    transformedImage = imtransform(dogImage,tform,'FillValues',0.0);
    fullscreen(transformedImage,2);
    pause
end
%imshow(transformedImage);