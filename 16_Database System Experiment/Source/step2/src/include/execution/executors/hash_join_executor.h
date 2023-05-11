//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// hash_join_executor.h
//
// Identification: src/include/execution/executors/hash_join_executor.h
//
// Copyright (c) 2015-2021, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "common/util/hash_util.h"
#include "execution/executor_context.h"
#include "execution/executors/abstract_executor.h"
#include "execution/expressions/abstract_expression.h"
#include "execution/plans/hash_join_plan.h"
#include "storage/table/tuple.h"

namespace bustub {

struct JoinKey {
  //同样要用到hash，这里hash的值为单独的value作为key
  Value key_;

  bool operator==(const JoinKey &other) const {
		return key_.CompareEquals(other.key_) == CmpBool::CmpTrue;
  }
};
}  // namespace bustub
namespace std {
//该函数用于map中DistinctKey的哈希计算
/** Implements std::hash on AggregateKey */
template <>
struct hash<bustub::JoinKey> {
  std::size_t operator()(const bustub::JoinKey &agg_key) const {
    size_t curr_hash = 0;
    if (!agg_key.key_.IsNull()) {
      curr_hash = bustub::HashUtil::CombineHashes(curr_hash, bustub::HashUtil::HashValue(&(agg_key.key_)));
    }
    return curr_hash;
  }
};
}  // namespace std

namespace bustub {

/**
 * HashJoinExecutor executes a nested-loop JOIN on two tables.
 */
class HashJoinExecutor : public AbstractExecutor {
 public:
  /**
   * Construct a new HashJoinExecutor instance.
   * @param exec_ctx The executor context
   * @param plan The HashJoin join plan to be executed
   * @param left_child The child executor that produces tuples for the left side of join
   * @param right_child The child executor that produces tuples for the right side of join
   */
  HashJoinExecutor(ExecutorContext *exec_ctx, const HashJoinPlanNode *plan,
                   std::unique_ptr<AbstractExecutor> &&left_child, std::unique_ptr<AbstractExecutor> &&right_child);

  /** Initialize the join */
  void Init() override;

  /**
   * Yield the next tuple from the join.
   * @param[out] tuple The next tuple produced by the join
   * @param[out] rid The next tuple RID produced by the join
   * @return `true` if a tuple was produced, `false` if there are no more tuples
   */
  bool Next(Tuple *tuple, RID *rid) override;

  /** @return The output schema for the join */
  const Schema *GetOutputSchema() override { return plan_->OutputSchema(); };

 private:
  /** The NestedLoopJoin plan node to be executed. */
  const HashJoinPlanNode *plan_;

	//将左表（小表）哈希化，方便右表直接遍历以进行数据的定位和比较
  //左表可能出现key值相同的记录，所以用vector都存起来
  std::unordered_map<JoinKey, std::vector<Tuple>> left_map;
  std::unique_ptr<AbstractExecutor> left_child_;
  std::unique_ptr<AbstractExecutor> right_child_;
  std::vector<Tuple> res;
  std::vector<Tuple>::iterator iter;
};

}  // namespace bustub
