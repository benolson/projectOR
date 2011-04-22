cal1 = imread('cal1.png');
cal2 = imread('cal2.png');
fullscreen(cal2,2)
camImage = imageGrabberMex()/255.;
fullscreen(cal1,2)
camImageBlack = imageGrabberMex()/255.;
%imshow(camImage-camImageBlack);
diff = camImage - camImageBlack;

rdiff = diff(:,:,1);
gdiff = diff(:,:,2);
bdiff = diff(:,:,3);

meandiff = mean(diff,3);

[dummy, rmax] = max(rdiff(:) - meandiff(:));
[dummy, gmax] = max(gdiff(:) - meandiff(:));
[dummy, bmax] = max(bdiff(:) - meandiff(:));
[dummy, wmax] = max(meandiff(:));

cal3 = rgb2gray(cal2);
cal3(rmax) = 255;
cal3(gmax) = 255;
cal3(bmax) = 255;
cal3(wmax) = 255;

imshow(cal2);