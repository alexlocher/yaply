/**
 * This file is part of YaPLY (Yet Another PLY library).
 *
 * Copyright (C) 2016 Alex Locher <alocher at ethz dot ch> (ETH Zuerich)
 * For more information see <https://github.com/alexlocher/yaply>
 *
 */

#include <yaply/YaPLY.hpp>
#include <Eigen/Dense>

int main() {

	{
		// generate 1000 random 3D points and RGB colors
		Eigen::Matrix<double, Eigen::Dynamic, 3> randPoints(1000, 3);
		randPoints << Eigen::Matrix<double, Eigen::Dynamic, 3>::Random(1000, 3);
		Eigen::Matrix<unsigned char, Eigen::Dynamic, 3> randColors(1000, 3);
		randColors << Eigen::Matrix<unsigned char, Eigen::Dynamic, 3>::Random(1000, 3);

		// generate a file with random 1000 3D points with colors
		yaply::PlyFile plyFile;
		plyFile["vertex"].nrElements = randPoints.rows();
		plyFile["vertex"].setScalars("x,y,z", randPoints.data());
		plyFile["vertex"].setScalars("red,green,blue", randColors.data());

		// save it
		plyFile.save("random.ply", true);
		std::cout << "created PLY file with random points and colors and saved it to >random.ply<"
				<< std::endl;
	}

	// Load a file and save it and save XYZ as ASCII
	{
		std::string inFile("random.ply");
		yaply::PlyFile plyFile(inFile.c_str());

		std::cout << "loaded file " << inFile << ":" << std::endl;
		for (const auto& el : plyFile.elements_) {
			std::cout << "element " << el.name << " " << el.nrElements << std::endl;
			for (const auto& p : el.properties)
				std::cout << "property " << p->name << std::endl;
		}

		auto& vertices = plyFile["vertex"];
		if (vertices.nrElements <= 0) {
			std::cerr << "could not find vertex attribute in the plyfile" << std::endl;
			return EXIT_FAILURE;
		}

		std::vector<double> x, y, z;
		if (vertices.getScalarProperty("x", x) && vertices.getScalarProperty("y", y)
				&& vertices.getScalarProperty("z", z)) {
			yaply::PlyFile outFile;
			outFile["vertex"].nrElements = x.size();
			outFile["vertex"].setScalars("x", x.data());
			outFile["vertex"].setScalars("y", y.data());
			outFile["vertex"].setScalars("z", z.data());

			outFile.save("random_ascii.ply", false);
		}
	}
}
