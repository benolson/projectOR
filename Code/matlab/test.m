points1 = [floor(linspace(20,1004,10));floor(linspace(20,748,10))]';
points2 = [floor(linspace(1004,20,10));floor(linspace(20,748,10))]';
colors = ones(3,15)';
cal0 = gen_calibrate_image([],[]);
cal1 = gen_calibrate_image(points1,colors);
cal2 = gen_calibrate_image(points2,colors);

%cal1 = imread('cal1.png');
%cal2 = imread('cal2.png');
fullscreen(cal0,2);
pause(.3);
[camImageBlack ~] = grabImages();
fullscreen(cal1,2);
pause(.3);
[camImage1 ~] = grabImages();
fullscreen(cal2,2);
pause(.3);
[camImage2 ~] = grabImages();

h = size(camImageBlack, 1);
w = size(camImageBlack, 2);

pts = [];
pts_all = [];
for cal_img = {camImage1 camImage2}
	cand = [];
	diff = (cal_img{1} - camImageBlack);
	diff = imfilter(rgb2gray(diff), fspecial('gaussian', 50, 4));
    %imshow(diff);
    %pause;
	for count = 1:15
    	[dummy, dmax] = max(diff(:));
    	[r c] = ind2sub(size(diff), dmax);
    	rr = max(1,r-25):min(h,r+25);
    	cr = max(1,c-25):min(w,c+25);
    	diff(rr,cr) = 0;
    	cand = [cand; r c];
    end
    cand
    pts_fit = fitline(cand,10,5)
	pts_fit = sortrows(pts_fit, 1);
	pts = [pts; pts_fit]
    pts_all = [pts_all; cand];
end


for i=1:20
    tx = pts(i,1);
    ty = pts(i,2);
    camImageBlack(tx-1:tx+1, ty-1:ty+1) = 255;
end
imshow(camImageBlack/255.);

% 
% %imshow(camImage-camImageBlack);
% diff = camImage - camImageBlack;
% 
% h = fspecial('gaussian',10,10);
% diff=imfilter(diff,h);
% 
% rdiff = im2double(diff(:,:,1));
% gdiff = im2double(diff(:,:,2));
% bdiff = im2double(diff(:,:,3));
% 
% meandiff = mean(diff,3);
% 
% %[dummy, rmax] = max(rdiff(:) - meandiff(:));
% h = size(diff, 1);
% w = size(diff, 2);
% d = rdiff - meandiff;
% pts = []
% for channel = 1:4
% cand = []
% if channel == 1
%     d = rdiff - meandiff;
% elseif channel == 2
%     d = gdiff - meandiff;
% elseif channel == 3
%     d = bdiff - meandiff;
% else
%     d = meandiff;
% end
% for count = 1:4
%     %imshow(d);
%     %pause;
%     [dummy, rmax] = max(d(:));
% 	[r c] = ind2sub(size(diff), rmax);
% 	rr = max(1,r-25):min(w,r+25);
% 	cr = max(1,c-25):min(h,c+25);
% 	d(rr,cr) = 0;
% 	cand = [cand; r c];
% end
% cand = sortrows(cand, 1);
% pts = [pts; cand];
% end
% 
% for i=1:16
%     d(pts(i,1), pts(i,2)) = 255;
% end
% imshow(d/255.);


%[dummy, gmax] = max(gdiff(:) - meandiff(:));
%[dummy, bmax] = max(bdiff(:) - meandiff(:));
%[dummy, wmax] = max(meandiff(:));
    %inpoints = [rmax_x rmax_y; gmax_x gmax_y; bmax_x bmax_y; wmax_x wmax_y];
   
%     basepoints = [20 20; ...
%                   20 433; ...
%                   20 847; ...
%                   20 1260; ...
%                   273 20; ...
%                   273 433; ...
%                   273 847; ...
%                   273 1260; ...
%                   527 20; ...
%                   527 433; ...
%                   527 847; ...
%                   527 1260; ...
%                   780 20; ...
%                   780 433; ...
%                   780 847; ...
%                   780 1260;];
                  
%    basepoints = c*[0 0; 0 1280; 800 1280; 800 0];

    %basepoints = [basepoints(:,2) basepoints(:,1)];
    basepoints = [points1;points2];
    
    % move origin to center
    %basepoints(:,1) = basepoints(:,1) - 640;
    %basepoints(:,2) = basepoints(:,2) - 400;
    
    %pts(:,1) = pts(:,1) - 300;
    %pts(:,2) = pts(:,2) - 400;
    
    pts = [pts(:,2) pts(:,1)];
    
    scaler = 1024/800 %984 / (max(pts(:,1)) - min(pts(:,1)))    
    scalec = 768/600%728 / (max(pts(:,2)) - min(pts(:,2)))

    
    
    
    pts(:,1) = pts(:,1) * scaler;
    pts(:,2) = pts(:,2) * scalec;

    img_scale_x = max([mean(pts(:,1) - min(pts(:,1))) ...
                    max(pts(:,1) - mean(pts(:,1)))])/1024
    img_scale_y = max([mean(proj_pts(:,2) - min(proj_pts(:,2))) ...
                    max(proj_pts(:,2) - mean(proj_pts(:,2)))])/768
    basepoints = basepoints*min(img_scale_x,img_scale_y);
    
%    for scalefactor = 1.5:.1:2.5
    
    %[tform, H] = findHomography(basepoints, pts);
    
    tform = cp2tform(pts, basepoints, 'projective');

    %[tform, H2] = findHomography(pts, basepoints);
   
    dogImage = imread('im.png');
    %Hf = H2^(-1);
    pads=0;
    while false
        corners = zeros(4,3);
        corners(1,:) = Hf*[-383+pads*30 -511+pads*40 1]';
        corners(2,:) = Hf*[-383+pads*30 512-pads*40 1]';
        corners(3,:) = Hf*[384-pads*30 512-pads*40 1]';
        corners(4,:) = Hf*[384-pads*30 -511+pads*40 1]';
        %corners(:,1:2)
        if ((max(corners(:,1))-min(corners(:,1)) < 800) && ...
                (max(corners(:,2))-min(corners(:,1)) < 1200))
            break;
        end
        pads = pads+1;
        scaledImg = imresize(padarray(dogImage, [30*pads 40*pads]), [768 1024]);
    end
    
    %scaledImg = imresize(padarray(dogImage, [0 0]), [768 1024]);
    transformedImage = imtransform(scaledImg,tform,'FillValues',0.0);
    fullscreen(transformedImage,2);
    pause(0.3);
    imshow(grabImages());
    
%    end
    %imshow(transformedImage);
    
%imshow(transformedImage);