#include <vector>
#include <cstddef>

// Simple struct to store a screw position
struct Screw
{
	double x;
	double y;
	double z;
};

// Container for managing a list of screws
class ScrewList
{
public:
	// Add a new screw
	void addScrew(double x, double y, double z)
	{
		screws_.push_back(Screw{x, y, z});
	}

	// Get the current number of stored screws
	std::size_t getCount() const
	{
		return screws_.size();
	}

	// true if there are no screws in the list
	bool isEmpty() const
	{
		return screws_.empty();
	}

	// Return the last screw and remove it from the list
	Screw takeLastScrew()
	{
		Screw s = screws_.back();
		screws_.pop_back();
		return s;
	}

private:
	std::vector<Screw> screws_;
};

