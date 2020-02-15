#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct node
{
    string parent = "";
    string child1 = "";
    string child2 = "";
};

struct orbit
{
    string center = "";
    string sat = "";
};

orbit parseOrbit(string input)
{
    orbit map;
    int index = input.find(")");
    map.center = input.substr(0, index);
    map.sat = input.substr(index + 1, input.length());
    return map;
}

node addChild(node obj, string sat)
{
    if(obj.child1 == "")
    {
        obj.child1 = sat;
    }
    else
    {
        obj.child2 = sat;
    }
    return obj;
}

node addParent(node obj, string center)
{
    obj.parent = center;
    return obj;
}

map<string, node> addCenter(map<string, node> links, orbit orbit)
{
    node center;
    if (links.find(orbit.center) != links.end())
    {
        // Did find an entry.  Add a new satellite to the node
        links[orbit.center] = addChild(links[orbit.center], orbit.sat);
    }
    else
    {
        // Didn't find an entry.  Make a new node with a satellite orbiting it
        links[orbit.center] = addChild(center, orbit.sat);
    }

    return links;
}

map<string, node> addSatellite(map<string, node> links, orbit orbit)
{
    node sat;
    if (links.find(orbit.sat) != links.end())
    {
        // Found an entry.  Add its parent
        links[orbit.sat] = addParent(links[orbit.sat], orbit.center);
    }
    else
    {
        // Didn't find an entry.  Add a new node for the satellite
        links[orbit.sat] = addParent(sat, orbit.center); 
    }

    return links;
}

int getParentConnection(map<string, node> links, string name)
{
    int count = 0;
    while (name != "COM")
    {
        name = links[name].parent;
        count++;
    }

    return count;
}

int main()
{
    ifstream in("part_one.txt");
    map<string, node> links;
    string str;
    while (getline(in, str))
    {
    	orbit map = parseOrbit(str);
        links = addCenter(links, map);
        links = addSatellite(links, map);
    }

    int x = 0;
    for (auto node : links)
    {
        string body = node.first;
        x += getParentConnection(links, body);
    }

    cout << "Total Connections: " << x << "\n";

    return 0;
}