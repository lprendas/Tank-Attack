/**************************************************************************/
/*  navigation_path_query_parameters2d.hpp                                */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

// THIS FILE IS GENERATED. EDITS WILL BE LOST.

#ifndef GODOT_CPP_NAVIGATION_PATH_QUERY_PARAMETERS2D_HPP
#define GODOT_CPP_NAVIGATION_PATH_QUERY_PARAMETERS2D_HPP

#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/core/class_db.hpp>

#include <type_traits>

namespace godot {

class NavigationPathQueryParameters2D : public RefCounted {
	GDEXTENSION_CLASS(NavigationPathQueryParameters2D, RefCounted)

public:

	enum PathfindingAlgorithm {
		PATHFINDING_ALGORITHM_ASTAR = 0,
	};

	enum PathPostProcessing {
		PATH_POSTPROCESSING_CORRIDORFUNNEL = 0,
		PATH_POSTPROCESSING_EDGECENTERED = 1,
	};

	enum PathMetadataFlags : uint64_t {
		PATH_METADATA_INCLUDE_NONE = 0,
		PATH_METADATA_INCLUDE_TYPES = 1,
		PATH_METADATA_INCLUDE_RIDS = 2,
		PATH_METADATA_INCLUDE_OWNERS = 4,
		PATH_METADATA_INCLUDE_ALL = 7,
	};

	void set_pathfinding_algorithm(NavigationPathQueryParameters2D::PathfindingAlgorithm pathfinding_algorithm);
	NavigationPathQueryParameters2D::PathfindingAlgorithm get_pathfinding_algorithm() const;
	void set_path_postprocessing(NavigationPathQueryParameters2D::PathPostProcessing path_postprocessing);
	NavigationPathQueryParameters2D::PathPostProcessing get_path_postprocessing() const;
	void set_map(const RID &map);
	RID get_map() const;
	void set_start_position(const Vector2 &start_position);
	Vector2 get_start_position() const;
	void set_target_position(const Vector2 &target_position);
	Vector2 get_target_position() const;
	void set_navigation_layers(uint32_t navigation_layers);
	uint32_t get_navigation_layers() const;
	void set_metadata_flags(BitField<NavigationPathQueryParameters2D::PathMetadataFlags> flags);
	BitField<NavigationPathQueryParameters2D::PathMetadataFlags> get_metadata_flags() const;
protected:
	template <class T, class B>
	static void register_virtuals() {
		RefCounted::register_virtuals<T, B>();
	}

public:

};

} // namespace godot

VARIANT_ENUM_CAST(NavigationPathQueryParameters2D::PathfindingAlgorithm);
VARIANT_ENUM_CAST(NavigationPathQueryParameters2D::PathPostProcessing);
VARIANT_BITFIELD_CAST(NavigationPathQueryParameters2D::PathMetadataFlags);

#endif // ! GODOT_CPP_NAVIGATION_PATH_QUERY_PARAMETERS2D_HPP