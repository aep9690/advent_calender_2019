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

int getParentConnection(map<string, node> links, string parent, int count)
{
    if (parent == "COM")
    {
        return 1;
    }
    else
    {
        string newParent = links[parent].parent;
        return count + getParentConnection(links, newParent, count);
    }
}

int main()
{
    ifstream in("orbit_01_ut.txt");
    map<string, node> links;
    string str;
    while (getline(in, str))
    {
    	orbit map = parseOrbit(str);
        links = addCenter(links, map);
        links = addSatellite(links, map);
    }

    for (auto node : links)
    {
        // int x = getParentConnection(links, node.second.parent, 0);
        // cout << node.first << " has " << x << " connections\n";
        cout << node.first << " orbits " << node.second.parent << " and has two satellites: ";
        cout << node.second.child1 << " and " << node.second.child2 << "\n";
    }

    return 0;
}