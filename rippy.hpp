#pragma once

#define _WIN32_WINNT 0x0601
#define VERSION "1.0"

#include <thread>
#include <asio.hpp>
#include <fstream>
#include <unordered_set>
#include <string>
#include <queue>

// filter mode
enum class filterMode {
    whitelist,
    blacklist
};

struct domainRule {
    std::string tag, attribute, has;
};

struct domainEntry {
    std::string domain, filter_mode;
    std::vector<std::string> start_pages, filter;
    std::vector<domainRule> rules;
};

class rippy {
public:
    rippy(asio::io_context& io_context, const std::string& user_agent, const std::vector<std::string>& visited_pages, const std::vector<domainEntry>& domains, int depth);
    void start();

private:
    asio::io_context& io_context;
    std::string user_agent;
    std::vector<std::string> visited_pages;
    std::vector<domainEntry> domains;
    int depth;
};

// The linkbuffer is used to keep track of which links have already been visited and which haven't.
class LinkBuffer {
    std::unordered_set<std::string_view> visited_links;
    std::queue<std::string> unvisited_links;
public:
    void checkAdd(const std::string& link); // check if link has been visited, if not, add it to the unvisited_links queue
    std::string getNext(); // get the next unvisited link
    bool isEmpty(); // check if there are any unvisited links
    size_t size(); // get the number of unvisited links
    size_t visitedSize(); // get the number of visited links
};