function stopCamera()
textFile = fopen('imageGrabber.txt', 'w');
fprintf(textFile, '%i',2);
fclose(textFile);
pause(3);
textFile = fopen('imageGrabber.txt', 'w');
fprintf(textFile, '%i',1);
end

