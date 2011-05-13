function [imgx imgy] = cam2imgspace(tform, camx, camy)

i = tform.tdata.T*[camx camy 1]';
imgx = i(1);
imgy = i(2);

end