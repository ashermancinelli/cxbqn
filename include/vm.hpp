#pragma once
#include <vector>
#include <cstdint>
#include <optional>
#include <memory>
#include <tuple>
#include <variant>

#include <value_types.hpp>

namespace cxbqn {

using u8 = uint8_t;
using u64 = uint64_t;
using uz = std::size_t;

namespace vm {

using Value = u64;
using Bytecode = std::vector<uz>;
using Objects = std::vector<std::optional<Value>>;
using Consts = std::vector<int>;

/**
 *
 * Bodies in a block are separated by `;`. Each entry in bodies is a list containing:
 * 
 * - Starting index in `code`
 * - Number of variables the block needs to allocate
 * - Variable names, as indices into the program's symbol list
 * - A mask indicating which variables are exported
 * 
 */
using Body = std::pair<u64, u64>;
using Bodies = std::vector<Body>;

/**
 *
 * Each entry in `blocks` is a list of the following properties:
 * 
 * - Block type: (0) function/immediate, (1) 1-modifier, (2) 2-modifier
 * - Block immediateness: (1) immediate or (0) deferred
 * - Index or indices in `bodies`
 * 
 */
enum BlockType { FunctionImmediate=0, Modifier1, Modifier2 };
enum BlockImmediateness { Deferred=0, Immediate };
using Block = std::tuple<
  BlockType
  , BlockImmediateness
  , std::variant<uz, std::vector<uz>>
>;
using Blocks = std::vector<Block>;

// Placeholders
using SourceLocations = int;
using TokenizationInfo = int;

/**
 *
 * \brief Holds all information for bytecode output from a bqn source generator.
 *
 * The complete bytecode for a program consists of the following:
 * 
 * - A bytecode sequence code
 * - A list consts of constants that can be loaded
 * - A list blocks of per-block information, described in the next section
 * - A list bodies of per-body information, described in the section after
 * - Optionally, source locations for each instruction
 * - Optionally, tokenization information
 * 
 * For example, the following snippet:
 * \code{.sh}
 * $ ./src/cjs.bqn '5‿5'
 *  [[0,0,0,0,11,2,7],[5],[[0,1,0]],[[0,0]]]
 * \endcode
 *
 * Would be parsed into code as:
 * \code{.cpp}
 * const auto c = Code{
 *   Bytecode{0,0,0,0,11,2,7},
 *   Consts{5},
 *   Blocks{{0,1,0}},
 *   Bodies{{0,0}}
 * };
 *
 * <a href="https://mlochbaum.github.io/BQN/implementation/vm.html#components">
 * See official BQN VM docs on the components for more information.</a>
 *
 */
struct Code {
  Bytecode bc;
  Objects objs;
  Consts consts;
  Blocks blks;
  Bodies bodies;
  std::optional<SourceLocations> sls;
  std::optional<TokenizationInfo> ti;
  Code() : sls{std::nullopt}, ti{std::nullopt} {}
};

struct Env { };
struct Sections {};

int vm(Env &e, Code& code, std::size_t &prog_counter, std::vector<int>& stack);
int run(Code &code, Objects &objects, Sections &sections);

}
}
