#pragma once

#include "common.h"

namespace LAB2 {

	struct Edge {
		std::array<size_t, 2> vertex;
		size_t weight;
		bool operator < (const Edge& rhs) const noexcept;
		friend std::ostream& operator << (std::ostream& out, const Edge& edge) noexcept;
	};

	//-------------------

	class FordBellman {

		using dist_t = std::variant<nullptr_t, size_t>;
	public:
		using count_vertex_t = size_t;
		using start_vertex_t = size_t;

		explicit FordBellman(std::string_view filename, count_vertex_t count_vertex, start_vertex_t start_vertex);

		void printHeader() const noexcept;
		void printShortCut() const noexcept;

	private:
		[[nodiscard]]
		bool loadEdge() noexcept;

		void calculateAlgorithm(size_t start) noexcept;

	private:
		std::string_view _filename;
		size_t _count_vertex;
		size_t _start_vertex;
		std::vector<std::pair<dist_t, size_t>> _dist;
		std::vector<Edge> _data_set;
	};
}