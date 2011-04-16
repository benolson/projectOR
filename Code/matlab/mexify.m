function mexify(filename)

eval(['mex ' filename ' -L/afs/ir/class/cs223b/lib/OpenCV-2.2.0/lib ' ...
    '-I/afs/ir/class/cs223b/lib/OpenCV-2.2.0/include -L/usr/lib64/ ' ...
    '-lopencv_core -lopencv_highgui -lopencv_ml -lopencv_features2d ' ...
    '-lopencv_objdetect -lopencv_imgproc -lopencv_video']);

%-lopencv_core  -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_imgproc -lopencv_video

end
