#include "MiniginPCH.h"
#include "ClipperHelper.h"
#include "clipper2/clipper.h"

using namespace Clipper2Lib;

void ClipperHelper::Test()
{
	Paths64 subject, clip, solution;
	subject.push_back(MakePath({ 100, 50, 10, 79, 65, 2, 65, 98, 10, 21 }));
	clip.push_back(MakePath({ 98, 63, 4, 68, 77, 8, 52, 100, 19, 12 }));
	solution = Difference(subject, clip, FillRule::NonZero);

	// Print the resulting paths
	for (const auto& path : solution) {
		for (const auto& point : path) {
			std::cout << "X: " << point.x << ", Y: " << point.y << std::endl;
		}
	}
}
