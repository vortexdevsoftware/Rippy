#pragma once

//#define _WIN32_WINNT 0x0601

#define VERSION "1.0"

#include <iostream>
#include <thread>
#include <fstream>
#include <unordered_set>
#include <string>
#include <queue>
#include <mutex>

// filter mode
enum class filterMode {
    whitelist,
    blacklist
};

struct domainRule {
    std::string tag, attribute, value;
};

struct domainEntry {
    std::string domain, filter_mode;
    std::vector<std::string> start_pages, filter;
    std::vector<domainRule> rules;
};

// config struct+
struct rippyConfig {
    std::string userAgent;
    unsigned int depth, threads;
    bool saveSession;
    std::vector<domainEntry> domains;
    std::vector<std::string> visitedPages;
};

// The linkbuffer is used to keep track of which links have already been visited and which haven't.
class LinkBuffer {
    std::unordered_set<std::string_view> visited_links;
    std::queue<std::string> unvisited_links;
public:
    void addToQueue(std::string_view link);
    void makeVisited(std::string_view link);
    std::string getNext(); // get the next unvisited link
    size_t visitedSize(); // number of visited links
    size_t queueSize();
};

// Rippy thread task function with reference to LinkBuffer, rippyConfig, and asio::io_context
void rippyTask(LinkBuffer&, const rippyConfig& config);