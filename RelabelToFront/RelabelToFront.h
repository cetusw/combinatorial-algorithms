#ifndef RELABELTOFRONT_H
#define RELABELTOFRONT_H
#include "Network.h"

class RelabelToFront {
public:
	RelabelToFront();
	int FindMaximumFlow(const Network& network);
	void PrintFlowMatrix() const;

private:
	void InitializePreflow();
	void Discharge(size_t vertex);
	void Relabel(size_t vertex);
	void Push(size_t edge);

	std::vector<size_t> m_height;
	std::vector<int> m_excessFlow;
	std::vector<size_t> m_current;
	Network m_network;
	int m_flow;
};



#endif //RELABELTOFRONT_H
