

class Graph {
    constructor(noOfVertices)
    {
        this.noOfVertices = noOfVertices;
        this.AdjList = new Map();
        this.AdjMatrix = new Array();
    }

    addVertex(v)
    {
        this.AdjList.set(v, []);
    }

    addEdge(v, w, value)
    {
        this.AdjList.get(v).push(new Map().set(w,value));
        this.AdjList.get(w).push(new Map().set(w,value));
    
    }

    printGraph()
    {
        var vertex = this.AdjList.keys();

        for (var i of vertex)
        {
            var get_values = this.AdjList.get(i);
            var conc = "";

            for (var j of get_values)
            {
                for (var f of j.keys()){
                    conc += f + ":" + j.get(f) + " ";  
                }
            }
            //for (var j of get_values)
              //  conc += j + " ";

            console.log(i + " -> " + conc);
        }
    }
}



function enviar() {
    
    var g = new Graph(6);
    var vertices = [ 'A', 'B', 'C', 'D', 'E', 'F' ];

    // adding vertices
    for (var i = 0; i < vertices.length; i++) {
        g.addVertex(vertices[i]);
    }

    // adding edges
    g.addEdge('A', 'B', 0);
    g.addEdge('A', 'D', 1);
    g.addEdge('A', 'E', 2);
    g.addEdge('B', 'C', 3);
    g.addEdge('D', 'E', 4);
    g.addEdge('E', 'F', 5);
    g.addEdge('E', 'C', 6);
    g.addEdge('C', 'F', 7);
    console.log(g.length());
    g.printGraph();
    
}


function dijkstra(graph, start) {

    var distances = [];
    //Initializing with a distance of "Infinity"
    for (var i = 0; i < graph.length; i++) {
        distances[i] = Number.MAX_VALUE;
    }
    //The distance from the start node to itself is of course 0
    distances[start] = 0;

    //This contains whether a node was already visited
    var visited = [];

    //While there are nodes left to visit...
    while (true) {
        // ... find the node with the currently shortest distance from the start node...
        var shortestDistance = Number.MAX_VALUE;
        var shortestIndex = -1;
        for (var i = 0; i < graph.length; i++) {
            //... by going through all nodes that haven't been visited yet
            if (distances[i] < shortestDistance && !visited[i]) {
                shortestDistance = distances[i];
                shortestIndex = i;
            }
        }

        console.log("Visiting node " + shortestDistance + " with current distance " + shortestDistance);

        if (shortestIndex === -1) {
            // There was no node not yet visited --> We are done
            return distances;
        }

        //...then, for all neighboring nodes....
        for (var i = 0; i < graph[shortestIndex].length; i++) {
            //...if the path over this edge is shorter...
            if (graph[shortestIndex][i] !== 0 && distances[i] > distances[shortestIndex] + graph[shortestIndex][i]) {
                //...Save this path as new shortest path.
                distances[i] = distances[shortestIndex] + graph[shortestIndex][i];
                console.log("Updating distance of node " + i + " to " + distances[i]);
            }
        }
        // Lastly, note that we are finished with this node.
        visited[shortestIndex] = true;
        console.log("Visited nodes: " + visited);
        console.log("Currently lowest distances: " + distances);

        return distances;
    }
}