// 2.8.6.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110206&format=html
//

#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
using namespace std;

string trim(const std::string& str, const std::string& whitespace = " \t")
{
	const string::size_type strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const string::size_type strEnd = str.find_last_not_of(whitespace);
	const string::size_type strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

class Name
{
public:

	Name()
	{
	}

	Name(const string& name) : fullName_(name)
	{
	}

	const string& FullName() const
	{
		return fullName_;
	}

private:
	string fullName_;
};

std::istream & operator>> (std::istream &in, Name& name)
{
	string firstName;
	in >> firstName;

	string lastName;

	char c = ':';

	in >> c;
	if (!in.good()) return in;

	while (c != ',' && c != ':')
	{
		lastName += c;

		in >> c;
		if (!in.good()) return in;
	}

	if (c == ':')
	{
		in.setstate(ios::eofbit);
	}

	firstName = trim(firstName);
	lastName = trim(lastName);

	name = Name(firstName + " " + lastName);

	return in;
}

vector<string> Names(const string &line)
{
	vector<string>  ret;
	string::size_type start = 0;
	string::size_type end = line.find(".,", start);

	while (end != string::npos)
	{
		ret.push_back(trim(line.substr(start, end - start + 1)));
		start = end + 2;
		end = line.find(".,", start);
	}

	if (start < line.length())
	{
		ret.push_back(trim(line.substr(start)));
	}

	return ret;
}

std::ostream & operator<< (std::ostream &out, const Name& name)
{
	out << name.FullName();

	return out;
}

bool operator<(const Name& name1, const Name& name2)
{
	return name1.FullName() < name2.FullName();
}

class Author
{
public:

	Author(const string& name) :
		name_(name),
		erdosNumber_(0),
		fVisited_(false)
	{
	}

	void Reset()
	{
		coAuthors_.clear();
		erdosNumber_ = 0;
	}

	const Name& FullName() const
	{
		return name_;
	}

	string ErdosNumber() const
	{
		if (erdosNumber_ == 0)
		{
			return "infinity";
		}

		ostringstream ostr;

		ostr << erdosNumber_;

		return ostr.str();
	}

	void AddCoAuthor(Author* author)
	{
		this->coAuthors_.insert(author);
		author->coAuthors_.insert(this);
	}

	void ComputeErdosNumber()
	{
		queue<Author*> que;
		que.push(this);
		this->fVisited_ = true;

		while (que.size())
		{
			Author* author = que.front();
			que.pop();

			for (set<Author*>::iterator iter = author->coAuthors_.begin(); iter != author->coAuthors_.end(); ++iter)
			{
				if ((*iter)->fVisited_) continue;

				if ((*iter)->erdosNumber_ == 0)
				{
					(*iter)->erdosNumber_ = author->erdosNumber_ + 1;
					que.push(*iter); (*iter)->fVisited_ = true;
				}
				else
				{
					if ((*iter)->erdosNumber_ > author->erdosNumber_ + 1)
					{
						(*iter)->erdosNumber_ = author->erdosNumber_ + 1;
						que.push(*iter); (*iter)->fVisited_ = true;
					}
				}
			}
		}
	}

private:
	::Name name_;
	set<Author*> coAuthors_;
	size_t erdosNumber_;
	bool fVisited_;
};

class ErdosNumbers
{
public:
	ErdosNumbers() :
		numScenarios_(0),
		curScenario_(0),
		P(0),
		N(0),
		erdos_(NULL)
	{
	}

	void Solve()
	{
		ReadNumberOfScenarios();

		while (ReadScenarioInput())
		{
			ComputeErdosNumbers();
			WriteScenarioOutput();
		}
	}

private:

	void ReadNumberOfScenarios()
	{
		string line;
		getline(cin, line);
		if (line.empty()) return;

		stringstream stream(line);
		stream >> numScenarios_;
	}

	bool ReadScenarioInput()
	{
		if (++curScenario_ > numScenarios_) return false;

		P = N = 0;

		string line;
		getline(cin, line);
		if (line.empty()) return false;

		stringstream stream(line);

		stream >> P;
		stream >> N;

		if (P == 0 || N == 0) return false;

		papers_.clear(); names_.clear();

		for (size_t i = 0; i < P; ++i)
		{
			string line, dummy;
			getline(cin, line, ':'); getline(cin, dummy);
			if (line.empty()) return false;

			papers_.push_back(trim(line));
		}

		for (size_t i = 0; i < N; ++i)
		{
			string line;
			getline(cin, line);
			if (line.empty()) return false;

			names_.push_back(trim(line));
		}

		return true;
	}

	void ComputeErdosNumbers()
	{
		ClearAuthorList();
		BuildPaperList();
		BuildAuthorList();
		erdos_->ComputeErdosNumber();
	}

	void WriteScenarioOutput()
	{
		cout << "Scenario " << curScenario_ << endl;

		for (size_t i = 0; i < vecAuthors_.size(); ++i)
		{
			cout << names_[i] << " " << vecAuthors_[i]->ErdosNumber() << endl;
		}
	}

	void BuildAuthorList()
	{
		for (size_t i = 0; i < N; ++i)
		{
			vector<string> name = Names(names_[i]);

			if (mapNameToAuthors_.count(Name(name.front())))
			{
				vecAuthors_.push_back(mapNameToAuthors_[Name(name.front())]);
			}
			else
			{
				mapNameToAuthors_[Name(names_[i])] = new Author(name.front());
				vecAuthors_.push_back(mapNameToAuthors_[Name(name.front())]);
			}
		}
	}

	void ClearAuthorList()
	{
		vecAuthors_.clear();
		vecAuthors_.reserve(N);

		for (map<Name, Author*>::iterator iter = mapNameToAuthors_.begin(); iter != mapNameToAuthors_.end(); ++iter)
		{
			delete iter->second;
		}

		mapNameToAuthors_.clear();

		erdos_ = mapNameToAuthors_[Name("Erdos, P.")] = new Author("Erdos, P.");
	}

	void BuildPaperList()
	{
		for (size_t i = 0; i < P; ++i)
		{
			vector<Author*> vecAuthors = GetAuthorsFromPaper(papers_[i]);

			if (vecAuthors.size() <= 1) continue;

			for (size_t i = 0; i < vecAuthors.size() - 1; ++i)
			{
				for (size_t j = i + 1; j < vecAuthors.size(); ++j)
				{
					(vecAuthors[i])->AddCoAuthor(vecAuthors[j]);
				}
			}
		}
	}

	vector<Author*> GetAuthorsFromPaper(const string& paper)
	{
		vector<Author*> ret;

		vector<string> names = Names(paper);

		for (size_t i = 0; i < names.size(); ++i)
		{
			Name authorName(names[i]);

			if (authorName.FullName().empty()) break;

			if (mapNameToAuthors_.count(authorName))
			{
				ret.push_back(mapNameToAuthors_[authorName]);
			}
			else
			{
				mapNameToAuthors_[authorName] = new Author(authorName.FullName());
				ret.push_back(mapNameToAuthors_[authorName]);
			}
		}

		return ret;
	}

private:
	size_t numScenarios_;
	size_t curScenario_;
	size_t P;
	size_t N;
	vector<Author*> vecAuthors_;
	map<Name, Author*> mapNameToAuthors_;

	vector<string> papers_;
	vector<string> names_;

	Author* erdos_;
};

int main()
{
	ErdosNumbers problem;
	problem.Solve();

	return 0;
}