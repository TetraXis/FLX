#pragma once

#include <cassert>
#include <vector>
#include <string>
#include <sstream>

#include <iostream>

#include "flx_types.hpp"

/// <summary>
/// 
/// DO NOT USE IT. UNDER WORK. Its broken.
/// 
/// This double linked list is backed by an std::vector
/// This allows for a cache frindly approach
/// Because std::vector will move data_ at some point,
/// nodes will use indexes to point to `next` and `prev`.
/// 
/// When moving nodes inside std::vector, neigbours should be updated.
/// 
/// When doing anything, that changes amount of elements or changes their order,
/// nodes in internal vector will get moved, thus invalidatin all pointers and iterators.
/// 
/// Two NULLNODES will act as sentinels
/// </summary>

namespace flx
{
	/// <summary>
	/// An std::vector baked doubly linked list for cache friendliness.
	/// !!! All iterators and pointers to elements will get invalid after
	/// any function call that changes amount of elements or changes their order.
	/// </summary>
	/// <typeparam name="ty"> - Type of data_</typeparam>
	template<typename ty>
	struct contiguous_doubly_linked_list
	{
		//static constexpr u64 NULLNODE = ~0ull;

		struct node
		{
			friend contiguous_doubly_linked_list;

		flx_private:
			u64 next{};
			u64 prev{};
			ty data{};

		flx_public:
			node() = default;
			node(const ty& new_data)
				: data(new_data)
			{
			}
			node(u64 new_next, u64 new_prev, const ty& new_data = {})
				: data(new_data), next(new_next), prev(new_prev)
			{
			}
		};

		struct iterator;
		struct const_iterator;
		template<typename iter_ty>
		struct reverse_iterator;

	flx_private:
		// front_sentinel
		static constexpr u64 front_idx = 0;
		// back_sentinel
		static constexpr u64 back_idx = 1;
		/// <summary>
		/// Add two sentinel nodes, that are cyled on themselves.
		/// Potentially, no bounds checks are needed.
		/// </summary>
		std::vector<node> nodes
		{
			{1, 0, {}},
			{1, 0, {}}
		};

	flx_public:

		ty& front();
		ty& back();
		const ty& front() const;
		const ty& back() const;

		void push_back(const ty&);
		ty pop_back();
		void push_front(const ty&);
		ty pop_front();
		iterator insert(const const_iterator&, const ty&);
		iterator erase(const const_iterator&);
		iterator erase(const const_iterator&, const const_iterator&);

		bool empty() const;
		void clear();
		u64 size() const;

		void swap(const const_iterator&, const const_iterator&);
		void reverse();
		void unique(const ty&);

		u64 capacity() const;
		void reserve(u64);
		void shrink_to_fit();
		node* data();
		const node* data() const;

		iterator begin();
		iterator end();

		const_iterator cbegin() const;
		const_iterator cend() const;

		reverse_iterator<iterator> rbegin();
		reverse_iterator<iterator> rend();

		reverse_iterator<const_iterator> crbegin() const;
		reverse_iterator<const_iterator> crend() const;

		std::string get_structure() const;

	flx_private:
		/// <summary>
		/// Moves erased element at the iterator to the back of a vector.
		/// Return iterator pointing where erased node was moved, in a way, fixing `erased` iterator.
		/// </summary>
		iterator imp_move_erased(const const_iterator&, const const_iterator&);
		bool imp_is_sentinel(const iterator&);
		bool imp_is_sentinel(const const_iterator&);

	flx_public:

		struct iterator
		{
			friend contiguous_doubly_linked_list;

		flx_private:
			std::vector<node>& nodes;
			u64 current_idx{};

		flx_public:

			iterator(std::vector<node>& ref, u64 idx)
				: nodes(ref), current_idx(idx)
			{
			}
			iterator(const reverse_iterator<iterator>& other)
				: nodes(other.iter.nodes), current_idx(other.iter.current_idx)
			{
			}
			void operator = (const iterator& other)
			{
				current_idx = other.current_idx;
			}

			ty& operator * ()
			{
				assert(current_idx < nodes.size() && "iterator * attempt on retrieving out of bounds");

				return nodes[current_idx].data;
			}
			ty* operator -> ()
			{
				assert(current_idx < nodes.size() && "iterator -> attempt on retrieving out of bounds");

				return &nodes[current_idx].data;
			}
			const ty& operator * () const
			{
				assert(current_idx < nodes.size() && "iterator const* attempt on retrieving out of bounds");

				return nodes[current_idx].data;
			}
			const ty* operator -> () const
			{
				assert(current_idx < nodes.size() && "iterator const-> attempt on retrieving out of bounds");

				return &nodes[current_idx].data;
			}

			iterator& operator ++ () // prefix ++
			{
				assert(current_idx < nodes.size() && "iterator attempt on ++ from out of bounds");

				current_idx = nodes[current_idx].next;
				return *this;
			}
			iterator& operator -- () // prefix --
			{
				assert(current_idx < nodes.size() && "iterator attempt on -- from out of bounds");

				current_idx = nodes[current_idx].prev;
				return *this;
			}
			iterator operator + (u64 offset) const
			{
				iterator result(*this);
				while (offset-- > 0)
				{
					++result;
				}
				return result;
			}
			iterator operator - (u64 offset) const
			{
				iterator result(*this);
				while (offset-- > 0)
				{
					--result;
				}
				return result;
			}

			bool operator == (const iterator& other) const
			{
				return current_idx == other.current_idx && &nodes == &other.nodes;
			}
			bool operator != (const iterator& other) const
			{
				return current_idx != other.current_idx || &nodes != &other.nodes;
			}

			u64& prev_idx() const
			{
				assert(current_idx < nodes.size() && "iterator attempt on prev_idx() from out of bounds");

				return nodes[current_idx].prev;
			}
			u64& next_idx() const
			{
				assert(current_idx < nodes.size() && "iterator attempt on next_idx() from out of bounds");

				return nodes[current_idx].next;
			}
			/*const u64& prev_idx() const
			{
				assert(current_idx != NULLNODE && "iterator attempt on prev_idx() from NULLNODE");

				return nodes[current_idx].prev;
			}
			const u64& next_idx() const
			{
				assert(current_idx != NULLNODE && "iterator attempt on next_idx() from NULLNODE");

				return nodes[current_idx].next;
			}*/

		flx_private:

			node& prev() const
			{
				assert(current_idx < nodes.size() && "iterator attempt on prev() from out of bounds");

				return nodes[nodes[current_idx].prev];
			}
			node& next() const
			{
				assert(current_idx < nodes.size() && "iterator attempt on next() from out of bounds");

				return nodes[nodes[current_idx].next];
			}
			/*const node& prev() const
			{
				assert(current_idx != NULLNODE && "iterator attempt on prev() from NULLNODE");

				return nodes[nodes[current_idx].prev];
			}
			const node& next() const
			{
				assert(current_idx != NULLNODE && "iterator attempt on next() from NULLNODE");

				return nodes[nodes[current_idx].next];
			}*/
		}; // iterator

		struct const_iterator
		{
			friend contiguous_doubly_linked_list;

		flx_private:
			const std::vector<node>& nodes;
			u64 current_idx{};

		flx_public:

			const_iterator(const std::vector<node>& ref, u64 idx)
				: nodes(ref), current_idx(idx)
			{
			}
			const_iterator(const iterator& iter)
				: nodes(iter.nodes), current_idx(iter.current_idx)
			{
			}
			const_iterator(const reverse_iterator<iterator>& other)
				: nodes(other.iter.nodes), current_idx(other.iter.current_idx)
			{
			}
			const_iterator(const reverse_iterator<const_iterator>& other)
				: nodes(other.iter.nodes), current_idx(other.iter.current_idx)
			{
			}
			void operator = (const const_iterator& other)
			{
				current_idx = other.current_idx;
			}

			const ty& operator * () const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on const* retrieving from out of bounds");

				return nodes[current_idx].data;
			}
			const ty* operator -> () const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on const-> retrieving from out of bounds");
				return &nodes[current_idx].data;
			}

			const_iterator& operator ++ () // prefix ++
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on ++ from out of bounds");
				current_idx = nodes[current_idx].next;
				return *this;
			}
			const_iterator& operator -- () // prefix --
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on -- from out of bounds");
				current_idx = nodes[current_idx].prev;
				return *this;
			}
			const_iterator operator + (u64 offset) const
			{
				const_iterator result(*this);
				while (offset-- > 0)
				{
					++result;
				}
				return result;
			}
			const_iterator operator - (u64 offset) const
			{
				const_iterator result(*this);
				while (offset-- > 0)
				{
					--result;
				}
				return result;
			}

			bool operator == (const const_iterator& other) const
			{
				return current_idx == other.current_idx && &nodes == &other.nodes;
			}
			bool operator != (const const_iterator& other) const
			{
				return current_idx != other.current_idx || &nodes != &other.nodes;
			}

			const u64& prev_idx() const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on prev_idx() from out of bounds");
				return nodes[current_idx].prev;
			}
			const u64& next_idx() const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on next_idx() from out of bounds");
				return nodes[current_idx].next;
			}

		flx_private:

			node& prev() const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on prev() from out of bounds");

				return const_cast<node&>(nodes[prev_idx()]);
			}
			node& next() const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on next() from out of bounds");

				return const_cast<node&>(nodes[next_idx()]);
			}
			u64& imp_prev_idx() const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on imp_prev_idx() from out of bounds");
				return const_cast<u64&>(nodes[current_idx].prev);
			}
			u64& imp_next_idx() const
			{
				assert(current_idx < nodes.size() && "const_iterator attempt on imp_next_idx() from out of bounds");
				return const_cast<u64&>(nodes[current_idx].next);
			}
		}; // const_iterator

		template<typename iter_ty>
		struct reverse_iterator
		{
			friend contiguous_doubly_linked_list;

		flx_private:
			iter_ty iter;

		flx_public:

			explicit reverse_iterator(const iter_ty& new_iter)
				: iter(new_iter)
			{
			}

			reverse_iterator<iter_ty>& operator ++ () // prefix ++
			{
				--iter;
				return *this;
			}
			reverse_iterator<iter_ty>& operator -- () // prefix --
			{
				++iter;
				return *this;
			}
			reverse_iterator<iter_ty> operator + (u64 offset) const
			{
				reverse_iterator<iter_ty> result(*this);
				while (offset-- > 0)
				{
					++result;
				}
				return result;
			}
			reverse_iterator<iter_ty> operator - (u64 offset) const
			{
				reverse_iterator<iter_ty> result(*this);
				while (offset-- > 0)
				{
					--result;
				}
				return result;
			}
			void operator = (const reverse_iterator<iter_ty>& other)
			{
				iter.current_idx = other.iter.current_idx;
			}

			/*ty& operator * ()
			{
				return *iter;
			}
			ty& operator -> ()
			{
				return *iter;
			}*/

			const ty& operator * () const
			{
				return *iter;
			}
			const ty& operator -> () const
			{
				return *iter;
			}

			bool operator == (const reverse_iterator<iter_ty>& other) const
			{
				return iter == other.iter;
			}
			bool operator != (const reverse_iterator<iter_ty>& other) const
			{
				return iter != other.iter;
			}

			u64& prev_idx() const
			{
				return nodes[iter.current_idx].next;
			}
			u64& next_idx() const
			{
				return nodes[iter.current_idx].prev;
			}

		flx_private:

			node& prev() const
			{
				assert(iter.current_idx < nodes.size() && "reverse_iterator attempt on prev() from out of bounds");

				return nodes[nodes[iter.current_idx].next];
			}
			node& next() const
			{
				assert(iter.current_idx < nodes.size() && "reverse_iterator attempt on next() from out of bounds");

				return nodes[nodes[iter.current_idx].prev];
			}
			/*const node& prev() const
			{
				assert(iter.current_idx != NULLNODE && "reverse_iterator attempt on prev() from NULLNODE");

				return nodes[nodes[iter.current_idx].next];
			}
			const node& next() const
			{
				assert(iter.current_idx != NULLNODE && "reverse_iterator attempt on next() from NULLNODE");

				return nodes[nodes[iter.current_idx].prev];
			}*/
		}; // reverse_iterator
	}; // contiguous_doubly_linked_list


	template<typename ty>
	inline ty& contiguous_doubly_linked_list<ty>::front()
	{
		return *begin();
	}

	template<typename ty>
	inline ty& contiguous_doubly_linked_list<ty>::back()
	{
		return *rbegin();
	}

	template<typename ty>
	inline const ty& flx::contiguous_doubly_linked_list<ty>::front() const
	{
		return *cbegin();
	}

	template<typename ty>
	inline const ty& flx::contiguous_doubly_linked_list<ty>::back() const
	{
		return *crbegin();
	}

	template<typename ty>
	inline void contiguous_doubly_linked_list<ty>::push_back(const ty& value)
	{
		const u64 new_idx = nodes.size();
		nodes.emplace_back(back_idx, nodes[back_idx].prev, value);
		nodes[nodes[back_idx].prev].next = new_idx;
		nodes[back_idx].prev = new_idx;
		return;
	}

	template<typename ty>
	inline ty contiguous_doubly_linked_list<ty>::pop_back()
	{
		assert(!empty() && "pop_back() called on empty list");

		ty value = *crbegin();

		imp_move_erased(crbegin(), { nodes, nodes.size() - 1 });
		nodes.pop_back();

		return value;
	}

	template<typename ty>
	inline void contiguous_doubly_linked_list<ty>::push_front(const ty& value)
	{
		const u64 new_idx = nodes.size();
		nodes.emplace_back(nodes[front_idx].next, front_idx, value);
		nodes[nodes[front_idx].next].prev = new_idx;
		nodes[front_idx].next = new_idx;
		return;
	}

	template<typename ty>
	inline ty contiguous_doubly_linked_list<ty>::pop_front()
	{
		assert(!empty() && "pop_front() called on empty list");

		ty value = *cbegin();

		imp_move_erased(cbegin(), { nodes, nodes.size() - 1 });
		nodes.pop_back();

		return value;
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::iterator contiguous_doubly_linked_list<ty>::insert(const contiguous_doubly_linked_list<ty>::const_iterator& where, const ty& value)
	{
		assert(where.current_idx != 0 && "insert() attempt with 'where' at front sentinel");
		assert(&where.nodes == &nodes && "insert() attempt with 'where' from other list");

		u64 new_idx = nodes.size();
		nodes.emplace_back(value);

		nodes[new_idx].next = where.current_idx;
		nodes[new_idx].prev = where.prev_idx();
		nodes[where.prev_idx()].next = new_idx;
		nodes[where.current_idx].prev = new_idx;

		return { nodes, new_idx };
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::iterator contiguous_doubly_linked_list<ty>::erase(const contiguous_doubly_linked_list<ty>::const_iterator& where)
	{
		assert(&where.nodes == &nodes && "erase() attempt with 'where' from other list");
		assert(!empty() && "erase() attempt on empty list");
		assert(where.current_idx < nodes.size() && "erase() attempt with 'where' out of bounds");



		iterator return_iter = imp_move_erased(where, { nodes, nodes.size() - 1 });


		//std::cout << "erase returned: " << return_iter.prev_idx() << " " << return_iter.current_idx << " " << return_iter.next_idx() << '\n';
		//std::cout << get_structure() << '\n';

		nodes.pop_back();
		return return_iter;
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::iterator contiguous_doubly_linked_list<ty>::erase(const contiguous_doubly_linked_list<ty>::const_iterator& first, const contiguous_doubly_linked_list<ty>::const_iterator& last)
	{
		assert(&first.nodes == &nodes && "erase() attempt with first iterator from other list");
		assert(&last.nodes == &nodes && "erase() attempt with last iterator from other list");
		assert(!empty() && "erase() attempt on empty list");
		assert(first.current_idx < nodes.size() && "erase() attempt with first iterator out of bounds");
		assert(last.current_idx < nodes.size() && "erase() attempt with last iterator out of bounds");

		if (first.current_idx == nodes[front_idx].next && last.current_idx == back_idx)
		{
			clear();
			return end();
		}

		const_iterator it = first;
		u64 distance = 0;

		while (it != last && it != cend())
		{
			/*std::cout << "{ nodes.size() - 1 - distance }: " <<  nodes.size() - 1 - distance << '\n';
			std::cout << get_structure() << '\n';*/

			// last is getting invalidated here
			it = imp_move_erased(it, { nodes, nodes.size() - 1 - distance });
			++it;
			++distance;
		}

		nodes.erase(nodes.end() - distance, nodes.end());

		return { nodes, last.current_idx };
	}

	template<typename ty>
	inline bool contiguous_doubly_linked_list<ty>::empty() const
	{
		return size() == 0;
	}

	template<typename ty>
	inline void contiguous_doubly_linked_list<ty>::clear()
	{
		nodes =
		{
			{1, 0, {}},
			{1, 0, {}}
		};
	}

	template<typename ty>
	inline u64 contiguous_doubly_linked_list<ty>::size() const
	{
		return nodes.size() - 2; // two elemts are sentinels
	}

	template<typename ty>
	inline void contiguous_doubly_linked_list<ty>::swap(const contiguous_doubly_linked_list<ty>::const_iterator& where_a, const contiguous_doubly_linked_list<ty>::const_iterator& where_b)
	{
		assert(where_a.current_idx < nodes.size() && "swap() attempt with first iterator out of bounds");
		assert(where_b.current_idx < nodes.size() && "swap() attempt with second iterator out of bounds");

		std::swap(nodes[where_a.current_idx].data, nodes[where_b.current_idx].data);
		return;
	}

	template<typename ty>
	inline void contiguous_doubly_linked_list<ty>::reverse()
	{
		for (u64 i = 2; i < nodes.size(); i++)
		{
			std::swap(nodes[i].next, nodes[i].prev);
		}
	}

	template<typename ty>
	inline void contiguous_doubly_linked_list<ty>::unique(const ty& value)
	{
		const_iterator it = cbegin();

		while (it != cend() && *it != value)
		{
			++it;
		}
		if (it == cend())
		{
			return;
		}
		++it;

		u64 erased_amount = 0;

		while (it != cend())
		{
			if (*it == value)
			{
				it = imp_move_erased(it, { nodes, nodes.size() - 1 - erased_amount });
				++erased_amount;
			}
			++it;
		}

		//// works
		//while (it != cend())
		//{
		//	if (*it == value)
		//	{
		//		std::cout << "it: " << it.prev_idx() << " " << it.current_idx  << " " << it.next_idx() << '\n';
		//		it = erase(it) - 1;
		//		//std::cout << get_structure() << '\n';
		//		std::cout << "new: " << it.prev_idx() << " " << it.current_idx << " " << it.next_idx() << '\n';
		//		std::cout << "\n\n";
		//	}
		//	++it;
		//}

		/*const_iterator cit = crbegin();

		while (cit != it && *cit == value)
		{
			--cit;
		}
		++cit;

		erase(cit, cend());

		u64 erased_amount = 0;

		for (; it != cend(); ++it)
		{
			std::cout << "\n\n";
			std::cout << " > it = " << it.current_idx << '\n';
			std::cout << " > next it = " << nodes[it.current_idx].next << '\n';
			std::cout << get_structure() << "\n\n";

			if (*it == value)
			{
				it = imp_move_erased(it, { nodes, nodes.size() - 1 - erased_amount });
				++erased_amount;
			}
		}

		nodes.erase(nodes.cend() - erased_amount, nodes.cend());*/

		return;
	}

	template<typename ty>
	inline u64 flx::contiguous_doubly_linked_list<ty>::capacity() const
	{
		return nodes.capacity();
	}

	template<typename ty>
	inline void flx::contiguous_doubly_linked_list<ty>::reserve(u64 new_cap)
	{
		nodes.reserve(new_cap);
		return;
	}

	template<typename ty>
	inline void flx::contiguous_doubly_linked_list<ty>::shrink_to_fit()
	{
		nodes.shrink_to_fit();
		return;
	}

	template<typename ty>
	inline flx::contiguous_doubly_linked_list<ty>::node* flx::contiguous_doubly_linked_list<ty>::data()
	{
		return nodes.data();
	}

	template<typename ty>
	inline const flx::contiguous_doubly_linked_list<ty>::node* flx::contiguous_doubly_linked_list<ty>::data() const
	{
		return nodes.data();
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::iterator contiguous_doubly_linked_list<ty>::begin()
	{
		return iterator(nodes, nodes[front_idx].next);
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::iterator contiguous_doubly_linked_list<ty>::end()
	{
		return iterator(nodes, back_idx);
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::const_iterator contiguous_doubly_linked_list<ty>::cbegin() const
	{
		return const_iterator(nodes, nodes[front_idx].next);
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::const_iterator contiguous_doubly_linked_list<ty>::cend() const
	{
		return const_iterator(nodes, back_idx);
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::reverse_iterator<typename contiguous_doubly_linked_list<ty>::iterator> contiguous_doubly_linked_list<ty>::rbegin()
	{
		return reverse_iterator<iterator>(iterator(nodes, nodes[back_idx].prev));
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::reverse_iterator<typename contiguous_doubly_linked_list<ty>::iterator> contiguous_doubly_linked_list<ty>::rend()
	{
		return reverse_iterator<iterator>(iterator(nodes, front_idx));
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::reverse_iterator<typename contiguous_doubly_linked_list<ty>::const_iterator> contiguous_doubly_linked_list<ty>::crbegin() const
	{
		return reverse_iterator<const_iterator>(const_iterator(nodes, nodes[back_idx].prev));
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::reverse_iterator<typename contiguous_doubly_linked_list<ty>::const_iterator> contiguous_doubly_linked_list<ty>::crend() const
	{
		return reverse_iterator<const_iterator>(const_iterator(nodes, front_idx));
	}

	template<typename ty>
	inline std::string flx::contiguous_doubly_linked_list<ty>::get_structure() const
	{
		std::stringstream ss{};

		ss << "Size: " << size() << ";\tTrue size: " << nodes.size() << ";\n";

		ss << "Nodes:\n";

		for (u64 i = 0; i < nodes.size(); i++)
		{
			ss << nodes[i].prev << " [" << i << ", {" << nodes[i].data << "}] " << nodes[i].next << "   ";
		}

		return ss.str();
	}

	template<typename ty>
	inline bool flx::contiguous_doubly_linked_list<ty>::imp_is_sentinel(const iterator& it)
	{
		return it.current_idx <= 1;
	}

	template<typename ty>
	inline bool flx::contiguous_doubly_linked_list<ty>::imp_is_sentinel(const const_iterator& it)
	{
		return it.current_idx <= 1;
	}

	template<typename ty>
	inline contiguous_doubly_linked_list<ty>::iterator contiguous_doubly_linked_list<ty>::imp_move_erased(const contiguous_doubly_linked_list<ty>::const_iterator& erased, const contiguous_doubly_linked_list<ty>::const_iterator& dest)
	{
		assert(!imp_is_sentinel(erased) && "imp_move_erased() called with 'erased' at sentinel");
		assert(!imp_is_sentinel(dest) && "imp_move_erased() called with 'dest' at sentinel");

		//iterator result = { nodes, erased.next_idx() };

		erased.next().prev = erased.prev_idx();
		erased.prev().next = erased.next_idx();

		if (erased.current_idx != dest.current_idx)
		{
			dest.next().prev = erased.current_idx;
			dest.prev().next = erased.current_idx;
			//erased.imp_prev_idx() = erased.next().prev; // in case `erased.next` == `dest`
			std::swap(nodes[erased.current_idx], nodes[dest.current_idx]);
		}

		//std::cout << "imp returned: " << dest.next().prev << " " << dest.next_idx() << " " << dest.next().next << '\n';
		//std::cout << get_structure() << '\n';

		return { nodes, dest.prev_idx() };

		/*std::cout << "imp_ called with:\n";
		std::cout << "er: " << erased.current_idx << '\n';
		std::cout << "de: " << dest.current_idx << '\n';*/

		/*if (erased.next_idx() == dest.current_idx)
		{
			dest.prev().next = erased.current_idx;
			dest.next().prev = erased.current_idx;

			erased.prev().next = erased.next_idx();
			erased.next().prev = erased.prev_idx();


			erased.imp_next_idx() = erased.current_idx;
		}
		else if (erased.prev_idx() == dest.current_idx)
		{
			erased.prev().next = erased.next_idx();
			erased.next().prev = erased.prev_idx();

			dest.prev().next = erased.current_idx;
			dest.next().prev = erased.current_idx;

			erased.imp_prev_idx() = erased.current_idx;
		}
		else
		{
			dest.prev().next = erased.current_idx;
			dest.next().prev = erased.current_idx;

			erased.prev().next = erased.next_idx();
			erased.next().prev = erased.prev_idx();
		}

		std::swap(nodes[erased.current_idx], nodes[dest.current_idx]);

		std::cout << '\n' << "imp_\n" << get_structure() << '\n';

		return { nodes, dest.current_idx };*/
	}
}