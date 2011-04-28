system('grabScreenshotAndCamerashot.exe');
cal1 = imread('cal1.png');
cal2 = imread('cal2.png');
fullscreen(cal2,2);
[camImage screenImage] = grabScreenshotAndCamerashot();
fullscreen(cal1,2);
[camImageBlack screenImage] = grabScreenshotAndCamerashot();

%imshow(camImage-camImageBlack);
diff = camImage - camImageBlack;

h = fspecial('gaussian',10,10);
diff=imfilter(diff,h);

rdiff = diff(:,:,1);
gdiff = diff(:,:,2);
bdiff = diff(:,:,3);

meandiff = mean(diff,3);

%[dummy, rmax] = max(rdiff(:) - meandiff(:));
h = size(diff, 1);
w = size(diff, 2);
d = rdiff - meandiff;
pts = []
for channel = 1:4
cand = []
if channel == 1
    d = rdiff - meandiff;
elseif channel == 2
    d = gdiff - meandiff;
elseif channel == 3
    d = bdiff - meandiff;
else
    d = meandiff;
end
for count = 1:4
    imshow(d);
    pause;
    [dummy, rmax] = max(d(:));
	[r c] = ind2sub(size(diff), rmax);
	rr = max(1,r-25):min(w,r+25);
	cr = max(1,c-25):min(h,c+25);
	d(rr,cr) = 0;
	cand = [cand; r c];
end
cand = sortrows(cand, 1);
pts = [pts; cand];
end

for i=1:16
    d(pts(i,1), pts(i,2)) = 255;
end
imshow(d)
pause;


%[dummy, gmax] = max(gdiff(:) - meandiff(:));
%[dummy, bmax] = max(bdiff(:) - meandiff(:));
%[dummy, wmax] = max(meandiff(:));
    %inpoints = [rmax_x rmax_y; gmax_x gmax_y; bmax_x bmax_y; wmax_x wmax_y];
   
    basepoints = [20 20; ...
                  20 433; ...
                  20 847; ...
                  20 1260; ...
                  273 20; ...
                  273 433; ...
                  273 847; ...
                  273 1260; ...
                  527 20; ...
                  527 433; ...
                  527 847; ...
                  527 1260; ...
                  780 20; ...
                  780 433; ...
                  780 847; ...
                  780 1260;];
                  
%    basepoints = c*[0 0; 0 1280; 800 1280; 800 0];

    basepoints = [basepoints(:,2) basepoints(:,1)];
    pts = [pts(:,2) pts(:,1)];
    tform = findHomography(basepoints,pts);
    dogImage = imread('im.jpg');
    transformedImage = imtransform(dogImage,tform,'FillValues',0.0);
    fullscreen(transformedImage,2);
    %imshow(transformedImage);
    
%imshow(transformedImage);