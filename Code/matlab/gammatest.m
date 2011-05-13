images = [];
for i = 0:32:256
	img = i/255 * ones(3,4);
	fullscreen(img,2);
	pause(0.3);
	images = cat(4, images, grabImages());
end