/*
 * INTEL CONFIDENTIAL
 * 
 * Copyright (C) 2022 Intel Corporation.
 * 
 * This software and the related documents are Intel copyrighted materials, and your use of
 * them is governed by the express license under which they were provided to you (License).
 * Unless the License provides otherwise, you may not use, modify, copy, publish, distribute,
 * disclose or transmit this software or the related documents without Intel's prior written permission.
 * 
 * This software and the related documents are provided as is, with no express or implied warranties,
 * other than those that are expressly stated in the License.
*/

#ifndef __STORAGE_VIDEO_INPUT_NODE_H_
#define __STORAGE_VIDEO_INPUT_NODE_H_

#include <media_storage.h>
#include <media_utility.h>
#include <s3_sdk.h>

#include "nodes/base/baseMediaInputNode.hpp"

namespace hce {

namespace ai {

namespace inference {

class StorageVideoInputNode : public baseMediaInputNode {
 public:
  StorageVideoInputNode(std::size_t totalThreadNum);

  virtual ~StorageVideoInputNode(){};

  /**
   * @brief Constructs and returns a node worker instance: StorageImageInputNodeWorker.
   * @param void
   */
  std::shared_ptr<hva::hvaNodeWorker_t> createNodeWorker() const override;

 private:
  hva::hvaConfigStringParser_t m_configParser;
};

class StorageVideoInputNodeWorker : public baseMediaInputNodeWorker {
 public:
  StorageVideoInputNodeWorker(hva::hvaNode_t* parentNode);

  void init() override;

  virtual const std::string nodeClassName() const override {
    return "StorageVideoInputNode";
  };

 private:
  /**
   * @brief to process media content from blob
   * @param buf buffer from blob, should be media_uri from video storage
   * @param content acquired media content
   * @param meta HceDatabaseMeta, can be updated
   * @param roi roi region, default be [0, 0, 0, 0]
   */
  virtual readMediaStatus_t processMediaContent(const std::string& buf, std::string& content,
                                   HceDatabaseMeta& meta, hva::hvaROI_t& roi, unsigned order = 0);

  std::string m_configmapFile;
  std::unique_ptr<hce::storage::Media_Storage> m_storageClient;
  boost::property_tree::ptree m_mediaAttribTree;
};

}  // namespace inference

}  // namespace ai

}  // namespace hce
#endif /*__STORAGE_VIDEO_INPUT_NODE_H_*/
