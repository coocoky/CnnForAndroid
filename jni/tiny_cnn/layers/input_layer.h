/*
    Copyright (c) 2013, Taiga Nomi
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once
#include "tiny_cnn/layers/layer.h"



namespace tiny_cnn {


	/*基本的层构造操作，以及前向传播的入口，和反向传播的终点，
	在这一层完成数据(图像矩阵)的输入以及前向传播的开始，
	同时准备接受反向传播的结果*/

class input_layer : public layer<activation::identity> {
public:
    typedef activation::identity Activation;
    typedef layer<activation::identity> Base;
    CNN_USE_LAYER_MEMBERS;

    input_layer() : Base(0, 0, 0, 0) {}

    cnn_size_t in_size() const override { return next_ ? next_->in_size(): static_cast<cnn_size_t>(0); }

    index3d<cnn_size_t> in_shape() const override { return next_ ? next_->in_shape() : index3d<cnn_size_t>(0, 0, 0); }
    index3d<cnn_size_t> out_shape() const override { return next_ ? next_->out_shape() : index3d<cnn_size_t>(0, 0, 0); }
    std::string layer_type() const override { return next_ ? next_->layer_type() : "input"; }

	/*前向传播*/
    const vec_t& forward_propagation(const vec_t& in, size_t index) override {
        Base::worker_specific_storage& ws = Base::get_worker_storage(index);
        ws.output_ = in;
        return next_ ? next_->forward_propagation(in, index) : ws.output_;
    }
	/*后向传播*/
    const vec_t& back_propagation(const vec_t& current_delta, size_t /*index*/) override {
        return current_delta;
    }

    const vec_t& back_propagation_2nd(const vec_t& current_delta2) override {
        return current_delta2;
    }

    size_t connection_size() const override {
        return in_size_;
    }

    size_t fan_in_size() const override {
        return 1;
    }

    size_t fan_out_size() const override {
        return 1;
    }
};

} // namespace tiny_cnn
