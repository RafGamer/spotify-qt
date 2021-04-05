#include "lib/spotify/spotifyapi.hpp"

using namespace lib::spt;

void api::album(const std::string &id, lib::callback<lib::spt::album> &callback)
{
	get(lib::fmt::format("albums/{}", id), callback);
}

void api::album_tracks(const lib::spt::album &album,
	lib::callback<std::vector<lib::spt::track>> &callback)
{
	get(lib::fmt::format("albums/{}/tracks?limit=50", album.id),
		"items", [album, callback](const std::vector<lib::spt::track> &results)
		{
			std::vector<lib::spt::track> tracks;
			tracks.reserve(results.size());
			for (auto &result : results)
			{
				lib::spt::track track = result;
				track.album = album.name;
				tracks.push_back(track);
			}
			callback(tracks);
		});
}
