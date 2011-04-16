function mexify(filename)

openCVLib = 'C:\OpenCV2.1\lib';
openCVInclude = 'C:\OpenCV2.1\include\opencv';

eval(['mex ' filename ' -L' openCVLib ' ' ...
    '-I' openCVInclude ' -LC:\Windows\SysWOW64 ' ...
    '-lcxcore210 -lhighgui210']);

%-lopencv_core  -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_imgproc -lopencv_video

end
