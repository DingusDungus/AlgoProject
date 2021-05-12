#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

//Struct for representing a link from a node to another
struct Link
{
    size_t linksTo;
    size_t cost;

    Link(size_t toLinkTo = -1, size_t linkCost = -1) : linksTo(toLinkTo), cost(linkCost)
    {
        // Empty
    }

    bool operator==(const Link& other)
    {
        return this->linksTo == other.linksTo;
    }
};

// Needed to be able to compare in a simpler way for find functions
struct special_compare
{
    explicit special_compare(const std::string &toLookFor) : toLookFor(toLookFor) {}
    bool operator() (const std::pair<std::string, std::vector<Link>>& element) { return element.first == toLookFor; }
    std::string toLookFor;
};

// Checks so that all nodes that exist in the original graph also exist in the mst
bool AllExistMSTCheck(const std::vector<std::string>& nodesFoundInMST,
                      const std::vector<std::pair<std::string, std::vector<Link>>>& nodesInOriginal)
{
    for(auto& node : nodesInOriginal)
    {
        if(std::find(nodesFoundInMST.begin(), nodesFoundInMST.end(), node.first) == nodesFoundInMST.end())
        {
            std::cout << "Error, node missing from graph" << std::endl;
            std::cout << "Expected to find node " << node.first << " but did not" << std::endl;
            return false;
        }
    }

    return true;
}

// Checks for cycles in the mst
bool RecursiveMSTCheck(std::vector<std::pair<std::string, std::vector<Link>>>& nodeVec,
                       std::vector<std::string>& foundNodes, Link toWorkWith)
{
    if(std::find(foundNodes.begin(), foundNodes.end(), nodeVec[toWorkWith.linksTo].first) != foundNodes.end())
    {
        std::cout << "Error, tree contains cycle!" << std::endl;
        std::cout << "Node: " << nodeVec[toWorkWith.linksTo].first << " was reached multiple times" << std::endl;
        return false;
    }

    foundNodes.push_back(nodeVec[toWorkWith.linksTo].first);

    for(auto& link : nodeVec[toWorkWith.linksTo].second)
    {
        // Remove link back to us so that we do not incorrectly find a cycle
        nodeVec[link.linksTo].second.erase(std::remove(nodeVec[link.linksTo].second.begin(),
                                         nodeVec[link.linksTo].second.end(), toWorkWith),
                                         nodeVec[link.linksTo].second.end());

        if(!RecursiveMSTCheck(nodeVec, foundNodes, link))
            return false;
    }

    return true;
}

/* 
   Compares the nodes between the mst file and original to 
   make sure no there are no extra, missing, or incorrect nodes
*/
bool CompareNodes(const std::vector<std::pair<std::string, std::vector<Link>>>& nodesInMST,
                  const std::vector<std::pair<std::string, std::vector<Link>>>& nodesInOriginal)
{
    if(nodesInOriginal.size() != nodesInMST.size())
    {
        std::cout << "Error, not a correct amount of nodes in answer file" << std::endl;
        std::cout << "Expected: " << nodesInOriginal.size() << ", got: " << nodesInMST.size() << std::endl;
        return false;
    }

    for(auto& node : nodesInOriginal)
    {
        if(std::find_if(nodesInMST.begin(), nodesInMST.end(), special_compare(node.first)) == nodesInMST.end())
        {
            std::cout << "Error, node missing from list of nodes in answer file" << std::endl; 
            std::cout << "Expected to find node " << node.first << " but did not" << std::endl;
            return false;
        }
    }

    return true;
}

/* 
   Compares the links between the mst file and original to 
   make sure no there are no incorrect links
*/
bool CompareLinks(std::vector<std::pair<std::string, std::vector<Link>>>& nodesInMST,
                  std::vector<std::pair<std::string, std::vector<Link>>>& nodesInOriginal)
{
    for(const auto& nodeMST : nodesInMST)
    {
        //find the same node in the original
        auto nodeOriginal = *std::find_if(nodesInOriginal.begin(), nodesInOriginal.end(),
                                       special_compare(nodeMST.first));

        for(const auto& linkMST : nodeMST.second)
        {
            auto nodeLinkLeadsToMST = nodesInMST[linkMST.linksTo];
            bool equivalentLinkInOriginal = false;
            for(const auto& linkOriginal : nodeOriginal.second)
            {
                if(nodesInOriginal[linkOriginal.linksTo].first == nodeLinkLeadsToMST.first &&
                   linkMST.cost == linkOriginal.cost)
                {
                    equivalentLinkInOriginal = true;
                    break;
                }
            }

            if(!equivalentLinkInOriginal)
            {
                std::cout << "Error, link found in mst that does not exist in original" << std::endl;
                std::cout << nodeMST.first << " - " << nodesInMST[linkMST.linksTo].first << std::endl;
                std::cout << "Cost of link: " << linkMST.cost << std::endl;
                return false;
            }
        }
    }
    return true;
}

// Read all nodes from a file into the vector containing nodes
bool ReadNodes(std::vector<std::pair<std::string, std::vector<Link>>>& nodes,
                  std::ifstream& file)
{
    std::string line;
    std::getline(file, line); // Read the first node
    while(line != "" && !file.eof())
    {
        nodes.push_back(std::make_pair(line, std::vector<Link>()));
        std::getline(file, line);
    } // Read all the existing nodes from the first part

    if(file.eof())
    {
        std::cout << "Error, file ended without any links" << std::endl;
        std::cout << "or perhaps the empty line separating nodes and links was absent" << std::endl;
        return false;
    }

    return true;
}

// Read all links from a file and associate them with the correct nodes
bool ReadLinks(std::vector<std::pair<std::string, std::vector<Link>>>& nodes,
                  std::ifstream& file, int& totalWeight)
{
    std::string line;
    while(!file.eof())
    {
        std::getline(file, line); // Read the line containing the link

        if(line == "" && file.eof()) // Take care of if there is an empty line at the end
            break;
		else if (line == "" && !file.eof())
		{
			std::cout << "Error when reading links, empty line without data found in file";
			return false;
		}

        size_t first_tab = line.find_first_of('\t');
        size_t last_tab = line.find_last_of('\t');

		if(first_tab == std::string::npos || last_tab == std::string::npos)
		{
			std::cout << "Error when reading links, one or both of the tabs that separate nodes and weights could not be found" << std::endl;
			std::cout << "Did you maybe use spaces instead of tabs?" << std::endl;
			return false;
		}

        std::string first = line.substr(0, first_tab);
        std::string second = line.substr(first_tab + 1, last_tab - first_tab - 1);
        Link link;
        try
        {
            link.cost = std::stoi(line.substr(last_tab + 1));
        }
        catch(const std::exception& e)
        {
            std::cout << "Error when reading weight in file, could not convert to a number\n";
            std::cout << "Got: " << line.substr(last_tab + 1) << std::endl;
            return false;
        }
        
        totalWeight += link.cost;
        auto firstNode = std::find_if(nodes.begin(), nodes.end(), special_compare(first));
        auto secondNode = std::find_if(nodes.begin(), nodes.end(), special_compare(second));

        if(firstNode == nodes.end() || secondNode == nodes.end())
        {
            std::cout << "Error, link " << first << " - " << second << std::endl;
            std::cout << "One or both of the nodes could not be found in the list of existing nodes" << std::endl;
            return false;
        }
        link.linksTo = secondNode - nodes.begin();
        firstNode->second.push_back(link);
        link.linksTo = firstNode - nodes.begin();
        secondNode->second.push_back(link);
    }

    return true;
}

// Function to read data from files for both original graph and the mst
bool ReadGraphsFromFiles(std::vector<std::pair<std::string, std::vector<Link>>>& nodesInMST,
                         std::ifstream& MSTGraph,
                         std::vector<std::pair<std::string, std::vector<Link>>>& nodesInOriginal,
                         std::ifstream& inputGraph,
                         int& totalWeightMST)
{
    if(!ReadNodes(nodesInOriginal, inputGraph) || !ReadLinks(nodesInOriginal, inputGraph, totalWeightMST))
    {
        std::cout << "Error when trying to read from original file" << std::endl;
        return false;
    }
    totalWeightMST = 0;
    if(!ReadNodes(nodesInMST, MSTGraph) || !ReadLinks(nodesInMST, MSTGraph, totalWeightMST))
    {
        std::cout << "Error when trying to read from answer file" << std::endl;
        return false;
    }

    return true;
}

// Function for checking so that the answer is a correct MST based on the original graph
bool CheckMSTAnswer(std::ifstream& inputGraph, std::ifstream& MSTGraph, unsigned short expectedWeight)
{
    std::string line;
    std::vector<std::pair<std::string, std::vector<Link>>> nodesInMST;
    std::vector<std::pair<std::string, std::vector<Link>>> nodesInOriginal;
    int totalWeightMST = 0;

    if(!ReadGraphsFromFiles(nodesInMST, MSTGraph, nodesInOriginal, inputGraph, totalWeightMST))
        return false;

    if(!CompareNodes(nodesInMST, nodesInOriginal) || !CompareLinks(nodesInMST, nodesInOriginal))
        return false;

    if(totalWeightMST != expectedWeight)
    {
        std::cout << "Error, MST weight not as expected" << std::endl;
        std::cout << "Expected: " << expectedWeight << " Got: " << totalWeightMST << std::endl;
        return false;
    }

    std::vector<std::string> foundNodes;
    if(!RecursiveMSTCheck(nodesInMST, foundNodes, 0) || !AllExistMSTCheck(foundNodes, nodesInOriginal))
        return false;

    return true;
}

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        std::cout << "Error, too few arguments, 3 expected" << std::endl;
		std::cout << "1: Graph file that was used to create MST" << std::endl;
		std::cout << "2: MST file produced by student code" << std::endl;
		std::cout << "3: Expected total weight of MST if correct" << std::endl;
        return -1;
    }

    std::cout << "Starting validation process" << std::endl;
    std::cout << "A \"finished\" message will be displayed when the validation process is done if no errors were detected" << std::endl;
    std::cout << "If the program ends without any error message(s) or a \"finished\" message then most likely a critical error exists in the answer file" << std::endl;

    std::ifstream inputGraph(argv[1]);
    std::ifstream MSTGraph(argv[2]);
	int expectedWeightOfMST = std::stoi(argv[3]);

	if(!inputGraph.is_open())
	{
        std::cout << "Error, could not open input file: " << argv[1] << std::endl;
		return -1;
	}

    if(!MSTGraph.is_open())
    {
        std::cout << "Error, could not open answer file: " << argv[2] << std::endl;
        return -1;
    }

    try
    {
        if(!CheckMSTAnswer(inputGraph, MSTGraph, expectedWeightOfMST))
        {
            std::cout << "One or more errors were detected during validation and need to be fixed" << std::endl;
            return -1;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "An error occurred: " << e.what() << std::endl;
        std::cout << "Check if answer file contains errors" << std::endl;
		return -1;
    }
    catch(...)
    {
        std::cout << "Unknown error occurred, check if answer file contains errors" << std::endl;
		return -1;
    }
    
    std::cout << "Finished validating answer without finding any errors" << std::endl;
    return 0;
}