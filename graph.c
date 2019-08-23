#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/**
* Créée un Graphe
* @param vertices Le nombre de sommets
* @param is_oriented Est-ce un graphe orienté ou non-orienté ?
* @return Le graphe créé
*/
Graph new_graph(int vertices, Bool is_oriented)
{
	int i;
	GraphElement *element;

	element = malloc(sizeof(*element));
	if(element == NULL)
	{
		fprintf(stderr, "Erreur : Probleme creation Graphe.\n");
		exit(EXIT_FAILURE);
	}
	element->is_oriented = is_oriented;
	element->nb_vertices = vertices;
	element->tab_neighbours = malloc(vertices * sizeof(AdjencyListElement));
	if(element->tab_neighbours == NULL)
	{
		fprintf(stderr, "Erreur : Probleme creation Graphe.\n");
		exit(EXIT_FAILURE);
	}
	for(i = 1 ; i < element->nb_vertices + 1 ; i++)
		element->tab_neighbours[i-1].begin = NULL;
	return element;
}

/*----------------------------------------------------------------------------------------------*/

/**
* Teste si un Graphe existe
* @param g Le Graphe à vérifier
* @return true Si le Graphe n'existe pas, false sinon
*/
Bool is_empty_graph(Graph g)
{
	if(g == NULL)
		return true;

	return false;
}

/*----------------------------------------------------------------------------------------------*/

/**
* Retourne un Noeud
* @param x La valeur du Noeud
* @param Le Noeud créé
*/
NodeList add_node(int x)
{
	NodeList n = malloc(sizeof(NodeListElement));

	if(n == NULL)
	{
		fprintf(stderr, "Erreur : Probleme creation Node.\n");
		exit(EXIT_FAILURE);
	}

	n->value = x;
	n->next = NULL;

	return n;
}

/*----------------------------------------------------------------------------------------------*/

/**
* Ajoute une arête à un Graphe
* @param g Le Graphe
* @param src Le premier sommet (ou source)
* @param dest Le second sommet (ou destination)
*/
void add_edge(Graph g, int src, int dest)
{
	NodeList n = add_node(dest);
	n->next = g->tab_neighbours[src-1].begin;
	g->tab_neighbours[src-1].begin = n;

	if(!g->is_oriented)
	{
		n = add_node(src);
		n->next = g->tab_neighbours[dest-1].begin;
		g->tab_neighbours[dest-1].begin = n;
	}
}

/*----------------------------------------------------------------------------------------------*/

/**
* Affiche un Graphe en mode console
* @param g Le Graphe
*/
void print_graph(Graph g)
{
	int i;

	for(i = 1 ; i < g->nb_vertices + 1 ; i++)
	{
		NodeList n = g->tab_neighbours[i-1].begin;
		printf("(%d) : ", i);

		while(n != NULL)
		{
			printf("%d, ", n->value);
			n = n->next;
		}

		printf("NULL\n");
	}
}

/*----------------------------------------------------------------------------------------------*/

/**
* Affiche un Graphe en 2D (avec Graphviz sous WINDOWS)
* @param g Le Graphe
*/
void display_graph(Graph g)
{
	//Windows seulement !
	if(g->is_oriented)
		system("%CD%/graphviz/bin/dotty.exe digraph.out");
	else
		system("%CD%/graphviz/bin/dotty.exe graph.out");
}

/*----------------------------------------------------------------------------------------------*/

/**
* Supprime un Graphe
* @param g Le Graphe
*/
void erase_graph(Graph g)
{
	if(is_empty_graph(g))
	{
		printf("Rien a effacer, le Graphe n'existe pas.\n");
		return;
	}

	//Si il existe des sommets adjacents
	if(g->tab_neighbours)
	{
		int i;

		for(i = 1 ; i < g->nb_vertices + 1 ; i++)
		{
			NodeList n = g->tab_neighbours[i-1].begin;
			
			while(n != NULL)
			{
				NodeList tmp = n;
				n = n->next;
				free(tmp);
			}
		}
		//Libération de la liste d'adjacence
		free(g->tab_neighbours);
	}
	//Libération du Graphe de la mémoire
	free(g);
}
