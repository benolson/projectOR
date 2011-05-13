q = imresize(grabImages(), [768 1024]);
dogImage = imread('im.png');
for i = randsample(size(proj_pts,1),10)'
dogImage(clamp(img_pts(i,2),768), clamp(img_pts(i,1),1024), :) = 0;
q(clamp(proj_pts(i,2),768), clamp(proj_pts(i,1),1024), :) = 0;
end

imshow([dogImage q])