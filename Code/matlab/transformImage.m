function transformedImage = transformImage(inputImage, inputTransformation)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

t_proj = maketform('projective',inputTransformation);   
transformedImage = imtransform(inputImage,t_proj,'FillValues',0.0);
end

