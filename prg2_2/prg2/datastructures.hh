// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <map>

// Type for town IDs
using TownID = std::string;

// Return value for cases where required town was not found
TownID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

struct TownData{
    TownID id_;
    TownID name_;
    TownID master_id_;
    std::vector<TownID> vassal_ids_;
    int x_;
    int y_;
    int tax_;
};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int size();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear();

    // Estimate of performance:
    // Short rationale for estimate:
    std::string get_name(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::pair<int, int> get_coordinates(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int get_tax(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> get_vassals(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> all_towns();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_town(TownID id, std::string const& name, int x, int y, int tax);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_town_name(TownID id, std::string const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> find_towns(std::string const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    TownID min_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID max_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID nth_distance(unsigned int n);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_town(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_distance_increasing_from(int x, int y);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);

private:
    // Add stuff needed for your class implementation here
    std::map<TownID,TownData> town_list_;
//    std::vector<TownID> vec_town_list_;
    std::multimap<TownID,TownData> alpha_town_list_;
    std::vector<TownID> alpha_town_vec_;
    std::multimap<int,TownData> dist_town_list_;
    std::vector<TownID> dist_town_vec_;
    std::vector<TownID> town_taxer_path_;
    std::vector<TownID> town_vassal_path_;
//    int total_tax_ = 0;
    bool dist_flag_ = false;

    void find_master_(TownID const& town_id);
    void find_vassal_(TownID const& town_id);
    int find_net_tax_(TownID const& town_id);
};

#endif // DATASTRUCTURES_HH
