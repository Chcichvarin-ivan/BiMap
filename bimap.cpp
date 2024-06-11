/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-06-08 14:39:21
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-06-10 23:08:21
 * @FilePath: /BiMap/bimap.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "bimap.h"
#include <deque>
#include <stdexcept>
#include <string>
#include <unordered_map>
struct KeyValue{
    std::string key;
    std::string value;
};
struct BiMap::Impl{
    bool Add(std::string_view& in_key, std::string_view& in_value){
        if((key_to_value_.count(in_key))||(value_to_key_.count(in_value))){
            return false;
       }

        try {
            items_.push_back({std::move(std::string(in_key)), std::move(std::string(in_value))});
  //          items_.push_front(std::move(in_key.data()));
  //          items_.push_back(std::move(in_value.data()));
        } catch (const std::bad_alloc&) {
            throw std::bad_alloc();
        }
        try {
            key_to_value_[items_.back().key] = items_.back().value;
            value_to_key_[items_.back().value] = items_.back().key;
        }catch (const std::bad_alloc&) {
            items_.pop_back();
            //items_.pop_front();
            throw std::bad_alloc();
        }catch (const std::out_of_range&){
            items_.pop_back();
            //items_.pop_front();
            throw std::out_of_range ("key value is out range");
        }
        return true;
    
    }

    std::optional<std::string_view> FindValue(std::string_view key) const noexcept {
        if(key_to_value_.count(key) > 0){
            return key_to_value_.at(key);
        }
        return std::nullopt;
    }

    std::optional<std::string_view> FindKey(std::string_view value) const noexcept {
         if(value_to_key_.count(value) > 0){
            return value_to_key_.at(value);
        }
        return std::nullopt;
    }

    Impl() = default;

    Impl(Impl&& other) {

        for(auto item: other.items_){
            items_.push_back({item.key,item.value});
            key_to_value_[std::string_view(items_.back().key)] = std::string_view(items_.back().value);
            value_to_key_[std::string_view(items_.back().value)] = std::string_view(items_.back().key);
        }
    }

    Impl(const Impl& other) {
        for(auto item: other.items_){
            items_.push_back({item.key,item.value});
            key_to_value_[std::string_view(items_.back().key)] = std::string_view(items_.back().value);
            value_to_key_[std::string_view(items_.back().value)] = std::string_view(items_.back().key);
        }
    }

    Impl& operator=(const Impl& other) {
        if (this != &other) {
            for(auto item: other.items_){
                items_.push_back({item.key,item.value});
                key_to_value_[std::string_view(items_.back().key)] = std::string_view(items_.back().value);
                value_to_key_[std::string_view(items_.back().value)] = std::string_view(items_.back().key);
            }
        }
        return *this;
    }

    Impl& operator=(Impl&& other) {
        if (this != &other) {
            for(auto item: other.items_){
                items_.push_back({item.key,item.value});
                key_to_value_[std::string_view(items_.back().key)] = std::string_view(items_.back().value);
                value_to_key_[std::string_view(items_.back().value)] = std::string_view(items_.back().key);
            }
       }
        return *this;
    }

private:
    std::unordered_map<std::string_view, std::string_view> key_to_value_;
    std::unordered_map<std::string_view, std::string_view> value_to_key_;
    std::deque<KeyValue> items_;
//    std::deque<std::string> items_;
};

BiMap::BiMap() : impl_(std::make_unique<Impl>()){
    
}

BiMap::~BiMap() = default;

BiMap::BiMap(BiMap&& other)noexcept: impl_(other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr){}

BiMap& BiMap::operator=(BiMap&& other)noexcept{
    if (this != std::addressof(other))
    {
        impl_ = other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr;
    }
    return *this;
}

BiMap::BiMap(const BiMap& other) : impl_(other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr){}

BiMap& BiMap::operator=(const BiMap& other)
{
    if (this != std::addressof(other))
    {
        impl_ = other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr;
    }
    return *this;
}

bool BiMap::Add(std::string_view key, std::string_view value) {
    
    return impl_->Add(key, value);
}

std::optional<std::string_view> BiMap::FindValue(std::string_view key) const noexcept {
    return impl_->FindValue(key);
}

std::optional<std::string_view> BiMap::FindKey(std::string_view value) const noexcept {
    return impl_->FindKey(value);
}