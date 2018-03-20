// Datastructures.cc

#include "datastructures.hh"
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}


Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

unsigned int Datastructures::size()
{
    return town_list_.size(); // Replace with actual implementation
}

void Datastructures::clear()
{
    // Replace with actual implementation
}

std::string Datastructures::get_name(TownID id)
{
    std::map<TownID,TownData>::iterator it = town_list_.find(id);
    if(it != town_list_.end()){
      std::string temp_name = it->second.name_;
      return temp_name;
    }
    return NO_NAME; // Replace with actual implementation
}

std::pair<int, int> Datastructures::get_coordinates(TownID id)
{
    std::map<TownID,TownData>::iterator it = town_list_.find(id);
    if(it != town_list_.end()){
      return {it->second.x_, it->second.y_};
    }
    return {NO_VALUE, NO_VALUE}; // Replace with actual implementation
}

int Datastructures::get_tax(TownID id)
{
    std::map<TownID,TownData>::iterator it = town_list_.find(id);
    if(it != town_list_.end()){
      return it->second.tax_;
    }
    return NO_VALUE; // Replace with actual implementation
}

std::vector<TownID> Datastructures::get_vassals(TownID id)
{
    std::map<TownID,TownData>::iterator it = town_list_.find(id);
    if(it != town_list_.end()){
      return it->second.vassal_ids_;
    }
    return {NO_ID}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> temp_vec_list;
    if(town_list_.size() > 0){
      for(auto it = town_list_.begin(); it != town_list_.end(); ++it){
        temp_vec_list.push_back(it->second.id_);
      }
      return temp_vec_list;
    }
    return {}; // Replace with actual implementation
}

bool Datastructures::add_town(TownID id, const std::string& name, int x, int y, int tax)
{
      std::map<TownID,TownData>::iterator it = town_list_.find(id);
      if(it == town_list_.end()){
//        std::cerr << id << " " << name << std::endl;
        TownData new_town_;
        new_town_.id_ = id;
        new_town_.name_ = name;
        new_town_.tax_ = tax;
        new_town_.x_ = x;
        new_town_.y_ = y;
        int new_town_distance = abs(x) + abs(y);
//        std::cerr << new_town_.id_ << new_town_.name_ << std::endl;
        town_list_.insert(std::pair<TownID,TownData>(id,new_town_));
        alpha_town_list_.insert(std::pair<TownID,TownData>(name,new_town_));
        dist_town_list_.insert(std::pair<int,TownData>(new_town_distance,new_town_));
        dist_flag_ =false;
        return true;
      }
    return false; // Replace with actual implementation
}

bool Datastructures::change_town_name(TownID id, const std::string& newname)
{
    if(town_list_.size()!=0){
        std::map<TownID,TownData>::iterator it = town_list_.find(id);
        if(it != town_list_.end()){
            it->second.name_ = newname;
            return true;
        }
    }
    return false; // Replace with actual implementation
}

bool Datastructures::remove_town(TownID id)
{
    if(town_list_.size()!=0){
        std::map<TownID,TownData>::iterator it = town_list_.find(id);
        if(it != town_list_.end()){
            if(it->second.master_id_!=""){
                if(it->second.vassal_ids_.size()!=0){
                    for(TownID vassal:it->second.vassal_ids_){
                        town_list_.find(vassal)->second.master_id_ = it->second.master_id_;
                        town_list_.find(it->second.master_id_)->second.vassal_ids_.push_back(vassal);
                    }
                }
                else{
                    town_list_.find(it->second.master_id_)->second.vassal_ids_ = {};
                }
            }
            else{
                if(it->second.vassal_ids_.size()!=0){
                    for(TownID vassal:it->second.vassal_ids_){
                        town_list_.find(vassal)->second.master_id_ = "";
                    }
                }
            }
            town_list_.erase(it);
            for(auto itr = alpha_town_list_.begin(); itr != alpha_town_list_.end(); ++itr){
                if(itr->second.id_ == id){
                    alpha_town_list_.erase(itr);
                    break;
                }
            }
            for(auto itr = dist_town_list_.begin(); itr != dist_town_list_.end(); ++itr){
                if(itr->second.id_ == id){
                    dist_town_list_.erase(itr);
                    break;
                }
            }
            dist_flag_ = false;
            return true;
        }
    }
    return false; // Replace with actual implementation
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    if (alpha_town_list_.size() != 0){
      alpha_town_vec_.clear();
      alpha_town_vec_.reserve(alpha_town_list_.size());
      for(auto itr = alpha_town_list_.begin(); itr != alpha_town_list_.end(); ++itr){
          alpha_town_vec_.push_back(itr->second.id_);
      }
      return alpha_town_vec_;
    }
    return {}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    if (dist_town_list_.size() != 0){
      if(dist_flag_){
          return dist_town_vec_;
      }
      else{
        dist_town_vec_.clear();
        dist_town_vec_.reserve(dist_town_list_.size());
        for(auto itr = dist_town_list_.begin(); itr != dist_town_list_.end(); ++itr){
            dist_town_vec_.push_back(itr->second.id_);
        }
        dist_flag_ = true;
        return dist_town_vec_;
      }
    }
    return {}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::find_towns(std::string const& name)
{
    std::vector<TownID> name_id;
    for(auto itr = town_list_.begin(); itr != town_list_.end(); ++itr){
      if(itr->second.name_ == name){
        name_id.push_back(itr->first);
      }
    }
    if(name_id.size() != 0){
      return name_id;
    }
    return {}; // Replace with actual implementation
}

TownID Datastructures::min_distance()
{
    if(dist_town_list_.size()!=0){
      if (dist_flag_){
          return dist_town_vec_[0];
      }
      else{
          dist_town_vec_.clear();
          dist_town_vec_.reserve(dist_town_list_.size());
          for(auto itr = dist_town_list_.begin(); itr != dist_town_list_.end(); ++itr){
              dist_town_vec_.push_back(itr->second.id_);
          }
          dist_flag_ = true;
          return dist_town_vec_[0];
      }
    }
    return NO_ID; // Replace with actual implementation
}

TownID Datastructures::max_distance()
{
    if(dist_town_list_.size()!=0){
      if (dist_flag_){
          return dist_town_vec_[dist_town_vec_.size() - 1];
      }
      else{
          dist_town_vec_.clear();
          dist_town_vec_.reserve(dist_town_list_.size());
          for(auto itr = dist_town_list_.begin(); itr != dist_town_list_.end(); ++itr){
              dist_town_vec_.push_back(itr->second.id_);
          }
          dist_flag_ = true;
          return dist_town_vec_[dist_town_vec_.size() - 1];
      }
    }
    return NO_ID; // Replace with actual implementation
}

TownID Datastructures::nth_distance(unsigned int n)
{
    if((dist_town_list_.size()!=0) && (n<dist_town_list_.size() && (n!=0))){
      if (dist_flag_){
            return dist_town_vec_[n-1];
      }
      else{
            dist_town_vec_.clear();
            dist_town_vec_.reserve(dist_town_list_.size());
            for(auto itr = dist_town_list_.begin(); itr != dist_town_list_.end(); ++itr){
                dist_town_vec_.push_back(itr->second.id_);
            }
            dist_flag_ = true;
            return dist_town_vec_[n - 1];
      }
    }
    return NO_ID; // Replace with actual implementation
}

std::vector<TownID> Datastructures::towns_distance_increasing_from(int x, int y)
{
    if(town_list_.size()!=0){
        if(x==0 && y==0){
            if(dist_flag_){
                return dist_town_vec_;
            }
            else{
              dist_town_vec_.clear();
              dist_town_vec_.reserve(dist_town_list_.size());
              for(auto itr = dist_town_list_.begin(); itr != dist_town_list_.end(); ++itr){
                  dist_town_vec_.push_back(itr->second.id_);
              }
              dist_flag_ = true;
              return dist_town_vec_;
            }
        }
        else{
            std::multimap<int, TownID> dist_town_xy_map;
            std::vector<TownID> dist_town_xy_vec;
            dist_town_xy_vec.clear();
            dist_town_xy_vec.reserve(dist_town_list_.size());
            for(auto itr = town_list_.begin(); itr != town_list_.end(); ++itr){
                int dist_xy = abs(itr->second.x_ - x)+ abs(itr->second.y_ - y);
                dist_town_xy_map.insert(std::pair<int,TownID>(dist_xy, itr->first));
            }
            for (auto itr = dist_town_xy_map.begin(); itr != dist_town_xy_map.end(); ++itr){
                dist_town_xy_vec.push_back(itr->second);
            }
            return dist_town_xy_vec;
        }
    }
    return {}; // Replace with actual implementation
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    std::map<TownID,TownData>::iterator it = town_list_.find(vassalid);
    if(it != town_list_.end() && it->second.master_id_==""){
        it->second.master_id_ = masterid;
        std::map<TownID,TownData>::iterator itr = town_list_.find(masterid);
        itr->second.vassal_ids_.push_back(vassalid);
        return true;
    }
    return false; // Replace with actual implementation
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    town_taxer_path_.clear();
    if(town_list_.size()!=0){
      std::map<TownID,TownData>::iterator it_town = town_list_.find(id);
      if(it_town != town_list_.end()){
          town_taxer_path_.push_back(it_town->first);
          town_taxer_path_.push_back(it_town->second.master_id_);
          find_master_(it_town->second.master_id_);

      }
      return town_taxer_path_;
    }
    return {}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    town_vassal_path_.clear();
    if(town_list_.size()!=0){
      std::map<TownID,TownData>::iterator it_town = town_list_.find(id);
      if(it_town != town_list_.end()){
          town_vassal_path_.push_back(it_town->first);
          find_vassal_(it_town->first);
      }
      return town_vassal_path_;
    }
    return {}; // Replace with actual implementation
}

int Datastructures::total_net_tax(TownID id)
{
    if(town_list_.size()!=0){
      std::map<TownID,TownData>::iterator it_town = town_list_.find(id);
      if(it_town != town_list_.end()){
          int total_tax = it_town->second.tax_;
          for(TownID vassal:it_town->second.vassal_ids_){
              total_tax = (int)floor(total_tax + find_net_tax_(vassal));
          }
          if(it_town->second.master_id_ == ""){
              return total_tax;
          }
          else{
              return (int)floor(0.9*total_tax);
          }
      }
    }
    return NO_VALUE; // Replace with actual implementation
}

void Datastructures::find_master_(TownID const& town_id){
    if(town_id!=""){
        std::map<TownID,TownData>::iterator it_town = town_list_.find(town_id);
        if(it_town->second.master_id_ != ""){
          town_taxer_path_.push_back(it_town->second.master_id_);
          find_master_(it_town->second.master_id_);
        }
    }
}

void Datastructures::find_vassal_(const TownID &town_id){
    if(town_id!=""){
        std::map<TownID,TownData>::iterator it_town = town_list_.find(town_id);
        if(it_town->second.vassal_ids_.size() != 0){
          for(TownID vassal: it_town->second.vassal_ids_){
              town_vassal_path_.push_back(vassal);
              find_vassal_(vassal);
          }
        }
    }
}

int Datastructures::find_net_tax_(const TownID &town_id){
    if(town_id!=""){
        std::map<TownID, TownData>::iterator it_town = town_list_.find(town_id);
        if(it_town->second.vassal_ids_.size() != 0){
          std::cerr << it_town->second.name_ << std::endl;
          int town_tax = it_town->second.tax_;
          int total_tax_from_vassal = 0;
          for(TownID vassal: it_town->second.vassal_ids_){
              total_tax_from_vassal = total_tax_from_vassal + find_net_tax_(vassal);
          }
    //      std::cerr << it_town->second.name_ << "**" << total_tax << std::endl;
          int total_tax = (int)floor(0.1*(town_tax + total_tax_from_vassal));
          return total_tax;
        }
        else{
          return (int)floor(0.1*it_town->second.tax_);
        }
    }
}
