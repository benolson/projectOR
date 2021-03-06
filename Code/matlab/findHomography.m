% Given pairs of corresponding points, returns the linear transformation
% corresponding to the least-squares solution
%  base_points and input_points are n x 2 matrices
%  TFORM goes from base -> input (?)
function [TFORM, H] = findHomography(base_points, input_points)
n = numel(base_points)/2;
A = [reshape([input_points(:,1)'; repmat(0,[1 n])], [2*n 1]) ...
     reshape([input_points(:,2)'; repmat(0,[1 n])], [2*n 1]) ...
     repmat([1; 0], [n 1]) ...
     reshape([repmat(0,[1 n]); input_points(:,1)'], [2*n 1]) ...
     reshape([repmat(0,[1 n]); input_points(:,2)'], [2*n 1]) ...
     repmat([0; 1], [n 1]) ...
     reshape([-1 * input_points(:,1)' .* base_points(:,1)'; ...
              -1 * input_points(:,1)' .* base_points(:,2)'], [2*n 1]) ...
     reshape([-1 * input_points(:,2)' .* base_points(:,1)'; ...
              -1 * input_points(:,2)' .* base_points(:,2)'], [2*n 1]) ...
     ];
b = reshape(base_points', [2*n 1]);
H = [(A' * A)^-1 * (A' * b); 1]
H = reshape(H, [3 3])
TFORM = maketform('projective',H^(-1));

end

