function best_pts = fitline(pts, k, j)
% given a set of points, takes the top k that form a line
% using a RANSAC-like method

n = size(pts, 1);
best_score = 999999;
best_pts = [];
for i = 1:50
	to_test = pts(randsample(n, j), :);
	[a b] = polyfit(to_test(:,1), to_test(:,2), 1)
	diffs = (pts(:,2) - a(2) - a(1).*pts(:,1)).^2;
	[dummy ind] = sort(diffs);
	score = sum(diffs(ind(1:k)))
	if score < best_score
    	best_score = score;
    	best_pts = pts(ind(1:k), :);
	end
end


end