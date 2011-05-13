function [img] = gen_calibrate_image(locations,colors)

img = zeros(768,1024,3);


function [img] = draw_circle(img_in,x,y,radius,color)
    img = img_in;
    for i=x-radius:x+radius
        for j=y-radius:y+radius

            if (i>0 && i<=1024 && ...
                j>0 && j<=1024 && ...
                ( (i-x)^2 + (j-y)^2 )^.5 < radius)
                img(j,i,:) = color;
            end
        end
    end
end


for i=1:size(locations,1)
    img = draw_circle(img,locations(i,1),locations(i,2),24,colors(i,:));
end



end