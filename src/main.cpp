#include <iostream>
#include <string>
#include <ctime>
#include <vector>

class Boot : public std::exception
{
public:
	Boot(const char* text) : exception(text) {};
};

class Fish : public std::exception
{
private:
	const char* text;
	int count;
public:
	Fish(const char* text, const int& count) { this->text = text; this->count = count; };

	const char* what() const override
	{
		std::cout << "Number of attempts: " << count << std::endl;
		return text;
	}
};

void catching_fish(int& temp, int& count, const std::vector<char> pond)
{
	count = 0;
	while (true)
	{
		std::cout << "Enter the casting sector of the fishing rod(1-9): ";
		std::cin >> temp;

		if (temp < 1 || temp > pond.size()) 
			throw std::exception("You didn't hit the pond.");

		--temp;

		if (pond[temp] != 'F' && pond[temp] != 'B')
		{
			std::cout << "There is nothing in this sector. " << std::endl;
			++count;
			continue;
		}
		else if (pond[temp] == 'F') 
			throw Fish("Congratulations! Have you caught a fish. ", count + 1);
		else if (pond[temp] == 'B')
			throw Boot("No luck! You caught the boot. ");
	}
}

int main()
{
	std::srand(time(NULL));
	std::vector<char> pond(9);
	int temp = rand() % pond.size();
	pond[temp] = 'F';
	int count = 0;
	
	while (count != 3)
	{
		int temp = rand() % pond.size();
		if (pond[temp] != 'F' && pond[temp] != 'B')
		{
			pond[temp] = 'B';
			++count;
		}
	}

	try
	{
		catching_fish(temp, count, pond);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "" << std::endl;
	}

	return 0;
}