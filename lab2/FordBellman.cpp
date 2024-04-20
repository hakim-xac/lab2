#include "FordBellman.h"

namespace LAB2 {

	//----------------------------

	bool Edge::operator < (const Edge& rhs) const noexcept
	{
		return weight < rhs.weight;
	}

	//----------------------------

	std::ostream& operator << (std::ostream& out, const Edge& edge) noexcept
	{
		out << "Vertexes2: [ " << edge.vertex[0] << ", " << edge.vertex[1] << " ]\n";
		out << "weight: " << edge.weight << "\n";
		out << "-------------\n";
		return out;
	}

	//----------------------------

	FordBellman::FordBellman(std::string_view filename, count_vertex_t count_vertex, start_vertex_t start_vertex)
		: _filename{ filename }
		, _count_vertex{ count_vertex }
		, _start_vertex{ start_vertex }
		, _dist{}
		, _data_set{}
	{
		if (loadEdge() == false) [[unlikely]]
			{
				std::cerr << "Error: can not load data from file!\n";
			}

			calculateAlgorithm(size_t{ 0 });
	}

	//----------------------------

	[[nodiscard]]
	bool
	FordBellman::loadEdge() noexcept
	{
		try
		{
			std::ifstream data_from_file{ _filename.data() };
			if (data_from_file.is_open() == false)
			{
				std::cerr << "Error: can not open the data file!\n";
				std::cerr << "filename: " << _filename << "\n";
				return {};
			}

			_data_set.reserve(_count_vertex);

			for (size_t i{ 0 }; i < _count_vertex; ++i)
			{
				for (size_t j{ }, skeep{ i + 1 }; j < skeep; ++j)
				{
					int32_t tmp{};
					data_from_file >> tmp;
				}

				for (size_t j{ i + 1 }; j < _count_vertex; ++j)
				{
					size_t tmp{};
					data_from_file >> tmp;

					_data_set.emplace_back(Edge{
						.vertex = { i, j },
						.weight = tmp
						});
				}
			}

			return _data_set.size() > 0;
		}
		catch (std::exception& ex)
		{
			std::cerr << "Exception: " << ex.what() << "\n";
			return false;
		}
	}

	//----------------------------

	void FordBellman::printShortCut() const noexcept
	{
		std::cout << "#" << std::setw(10) << " " << "ShortCut:" << std::setw(10) << "#\n";
		std::cout << std::setw(30) << std::setfill('=') << "\n" << std::setfill(' ');
		std::cout << "#" << std::setw(11) << "direction" << " | " << std::setw(9) << "weight" << std::setw(6) << "#\n";

		std::cout << std::setw(30) << std::setfill('=') << "\n" << std::setfill(' ');

		for (auto && elem : std::span{ _dist })
		{
			const size_t* dist_value{ std::get_if<size_t>(&elem.first) };
			if (dist_value)
			{
				std::cout << "#"  << std::setw(3) << _start_vertex + 1 << " -> " << std::setw(3) << elem.second + 1 << std::setw(4) << " | ";
				std::cout << std::setw(6) << *dist_value << std::setw(9) << "#\n";
			}
		}

		std::cout << std::setw(30) << std::setfill('=') << "\n" << std::setfill(' ');
	}

	//----------------------------

	void FordBellman::calculateAlgorithm(size_t start) noexcept
	{
		using dist_t = std::variant<size_t, nullptr_t>;
		try
		{
			_dist.resize(_count_vertex);

			_dist[start].first = size_t{};
			_dist[start].second = start;

			for (int i = 1; i <= _count_vertex - 1; ++i)
			{
				for (int j = 0; j < _data_set.size(); ++j)
				{
					size_t lhs{ _data_set[j].vertex[0] };
					size_t rhs{ _data_set[j].vertex[1] };
					size_t weight{ _data_set[j].weight };

					size_t* dist_lhs{ std::get_if<size_t>(&(_dist[lhs].first)) };
					size_t* dist_rhs{ std::get_if<size_t>(&(_dist[rhs].first)) };

					if (!dist_lhs)
						continue;

					size_t dist_lhs_weight{ *dist_lhs + weight };

					if (dist_rhs == nullptr || dist_lhs_weight < *dist_rhs)
					{
						_dist[rhs].first = dist_lhs_weight;
						_dist[rhs].second = rhs;
					}
				}
			}

			_dist.erase(std::remove_if(std::begin(_dist), std::end(_dist), [](auto dst) {
				auto fn{ std::get_if<size_t>(&dst.first) };
				return fn == nullptr || *fn == size_t{};
				}), std::end(_dist));
		}
		catch (std::exception& ex)
		{
			std::cerr << "Exception: " << ex.what() << "\n";
		}
	}

	//----------------------------

	void FordBellman::printHeader() const noexcept
	{
		std::cout << std::setw(30) << std::setfill('=') << "\n" << std::setfill(' ');
		std::cout << std::setw(10) << "Student:" << std::setw(20) << "Khakimov A.S.\n";
		std::cout << std::setw(10) << "Variant:" << std::setw(20) << "# 1\n";
		std::cout << std::setw(30) << std::setfill('=') << "\n" << std::setfill(' ');
	}

	//----------------------------
}