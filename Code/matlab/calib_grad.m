% Tries to find matching points based on gradient images

load('calib_imgs');


locs = [20 20 1004 1004; 20 748 748 20]';
colors = ones(3, 4)';
cal = gen_calibrate_image(locs,colors);

%{

fullscreen(black_img,2);
pause(.3);
black_raw = grabImages();
%fullscreen(white_img,2);
fullscreen(cal,2);
pause(.3);
white_raw = grabImages();
%fullscreen(horiz_img,2);
fullscreen((double(horiz_img)/255).^0.5,2);
pause(.3);
horiz_raw = grabImages();
%fullscreen(255-horiz_img,2);
fullscreen((double(255-horiz_img)/255).^0.5,2);
pause(.3);
horiz_raw2 = grabImages();
%fullscreen(vert_img,2);
fullscreen((double(vert_img)/255).^0.5,2);
pause(.3);
vert_raw = grabImages();
%fullscreen(255-vert_img,2);
fullscreen((double(255-vert_img)/255).^0.5,2);
pause(.3);
vert_raw2 = grabImages();

black = double(imresize(rgb2gray(black_raw), [150 200]));
white = double(imresize(rgb2gray(white_raw), [150 200]));
horiz = double(imresize(rgb2gray(horiz_raw), [150 200]));
vert = double(imresize(rgb2gray(vert_raw), [150 200]));
horiz2 = double(imresize(rgb2gray(horiz_raw2), [150 200]));
vert2 = double(imresize(rgb2gray(vert_raw2), [150 200]));

%}
img_pts = [];
proj_pts = [];

wmb = white-black;
corners = [];
for i = 1:150
    for j = 1:200
        %if white(i,j) - black(i,j) > 60
        if wmb(i,j) > 100
            x1 = 1024*(horiz(i,j)-black(i,j))./white(i,j);
            y1 = 768*(vert(i,j)-black(i,j))./white(i,j);
            x2 = 1024*(1 - ((horiz2(i,j)-black(i,j))./white(i,j)));
            y2 = 768*(1 - ((vert2(i,j)-black(i,j))./white(i,j)));
            %proj_pts = [proj_pts; j/200 i/150];
            %img_pts = [img_pts; (x1+x2)/2 (y1+y2)/2];
            
            x = x1+x2;
            y = y1+y2;
            corners = [corners; x y 4*j 4*i];
            
        	rr = max(1,i-25):min(150,i+25);
        	cr = max(1,j-25):min(200,j+25);
            wmb(rr,cr) = 0;
        end
    end
end

corners = sortrows(corners);
corners_left = sortrows(corners(1:2,:),2);
corners_right = sortrows(corners(3:4,:),2);

corners = [corners_left(1,3:4); corners_right(1,3:4); corners_right(2,3:4); corners_left(2,3:4)];

% Find largest rectangle with aspect ratio HERE
% =------=------=------ %



% =------=------=------ %

tform = cp2tform(corners,[1 1; 1 1024; 768 1024; 768 1],'projective');
return;

scaler = 1024; % / (max(proj_pts(:,1)) - min(proj_pts(:,1)))    
scalec = 768; % / (max(proj_pts(:,2)) - min(proj_pts(:,2)))

proj_pts(:,1) = proj_pts(:,1) * scaler;
proj_pts(:,2) = proj_pts(:,2) * scalec;

%img_scale_x = (max(proj_pts(:,1)) - min(proj_pts(:,1)))/1024/1.8
%img_scale_y = (max(proj_pts(:,2)) - min(proj_pts(:,2)))/768/1.8

%img_pts = img_pts*min(img_scale_x,img_scale_y);

%proj_pts = fliplr(proj_pts);
%img_pts = fliplr(img_pts);

%[tform, H2] = findHomography(proj_pts, img_pts);
samples = randsample(size(proj_pts(:,1),1),100);
tform = cp2tform(proj_pts(samples,:), img_pts(samples,:), 'projective');

dogImage = imread('im.png');

pads=0;
scaledImg = imresize(padarray(dogImage, [30*pads 40*pads]), [768 1024]);


transformedImage = imtransform(scaledImg,tform,'FillValues',0.0);
fullscreen(transformedImage,2);
pause(0.3);
imshow(grabImages());
