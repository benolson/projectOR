% Tries to find matching points based on gradient images

load('calib_imgs');

fullscreen(black_img,2);
pause(.3);
black = grabImages();
fullscreen(white_img,2);
pause(.3);
white = grabImages();
fullscreen(horiz_img,2);
pause(.3);
horiz = grabImages();
fullscreen(vert_img,2);
pause(.3);
vert = grabImages();

black = double(imresize(rgb2gray(black), [150 200]));
white = double(imresize(rgb2gray(white), [150 200]));
horiz = double(imresize(rgb2gray(horiz), [150 200]));
vert = double(imresize(rgb2gray(vert), [150 200]));

img_pts = [];
proj_pts = [];

for i = 1:150
    for j = 1:200
        if white(i,j) - black(i,j) > 50
            x = 1024*(horiz(i,j)-black(i,j))./white(i,j);
            y = 768*(vert(i,j)-black(i,j))./white(i,j);
            proj_pts = [proj_pts; 4*j 4*i];
            img_pts = [img_pts; x y];
        end
    end
end


scaler = 1024 / (max(proj_pts(:,1)) - min(proj_pts(:,1)))    
scalec = 768 / (max(proj_pts(:,2)) - min(proj_pts(:,2)))
proj_pts(:,1) = proj_pts(:,1) * scaler;
proj_pts(:,2) = proj_pts(:,2) * scalec;
[tform, H2] = findHomography(proj_pts, img_pts);

dogImage = imread('im.png');

pads=0;
while true
    corners = zeros(4,3);
    corners(1,:) = Hf*[-383+pads*30 -511+pads*40 1]';
    corners(2,:) = Hf*[-383+pads*30 512-pads*40 1]';
    corners(3,:) = Hf*[384-pads*30 512-pads*40 1]';
    corners(4,:) = Hf*[384-pads*30 -511+pads*40 1]';
    %corners(:,1:2)
    if ((max(corners(:,1))-min(corners(:,1)) < 768) && ...
            (max(corners(:,2))-min(corners(:,1)) < 1024))
        break;
    end
    pads = pads+1;
    scaledImg = imresize(padarray(dogImage, [30*pads 40*pads]), [768 1024]);
end



transformedImage = imtransform(scaledImg,tform,'FillValues',0.0);
fullscreen(transformedImage,2);
pause(0.3);
imshow(grabImages());
