// -*- mode:c++ -*-

template<const unsigned N,const  unsigned M=0>
struct inner_prod {
    template<typename IterU, typename IterV, typename ResType>
    static ResType sum (IterU u, IterV v, const ResType& init) {
        const ResType uvm = {*(u+M) * ResType{*(v+M)}};
        return uvm + inner_prod<N, M+1u>::sum(u, v, init);
    }
};

template<const unsigned N>
struct inner_prod<N,N> {
    template<typename IterU, typename IterV, typename ResType>
    static ResType sum (IterU u, IterV, const ResType& init) {
        return init;
    }

};

