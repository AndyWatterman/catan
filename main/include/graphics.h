#pragma once

//#include "header.h"

template <typename Resource, typename Identifier>
class Holder {
protected:
	std::map<Identifier, std::unique_ptr<Resource>> HolderMap;
	
public:	
	Resource& get(Identifier  id);
	const Resource& get(Identifier id) const;

	void load(Identifier id, const Resource & res);
};

template <typename Resource, typename Identifier>
Resource& Holder<Resource, Identifier>::get(Identifier id)
{
	auto found = HolderMap.find(id);
	assert(found != HolderMap.end());
	
	return *found->second;
};

template<typename Resource, typename Identifier>
inline const Resource & Holder<Resource, Identifier>::get(Identifier id) const
{
	auto found = HolderMap.find(id);
	assert(found != HolderMap.end());

	return *found->second;
};

template<typename Resource, typename Identifier>
inline void Holder<Resource, Identifier>::load(Identifier id, const Resource & res)
{
	std::unique_ptr<Resource> resource(new Resource(res));
	auto inserted = HolderMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

/*========================================================================*/

template <typename Resource, typename Identifier>
class ResourceHolder: public Holder<Resource, Identifier> {
public:
	void LoadFromFile(Identifier id, const std::string& filename);		
};

template<typename Resource, typename Identifier>
inline void ResourceHolder<Resource, Identifier>::LoadFromFile(Identifier id, const std::string & filename)
{		
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	
	auto inserted = Holder<Resource, Identifier>::HolderMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
};
