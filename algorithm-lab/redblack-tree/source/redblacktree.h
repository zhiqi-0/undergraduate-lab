
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

enum RBTColor{Red = 0, Black};

/* Note: User should offer a operator reload of '<' & '=' & '==' when this operator
 * of type <T> is not built-in. 
 */
template<typename T>
class RBTNode{
 public:
    RBTColor color_;
    RBTNode* lchild_;
    RBTNode* rchild_;
    RBTNode* parent_;
    T key_;
    std::size_t size;
    RBTNode();
    RBTNode(T key);
    RBTNode(RBTColor color, RBTNode* lchild, RBTNode* rchild, RBTNode* parent, T key);
    ~RBTNode() {};
};

/* RedBlack Tree Node Definition */

/* RedBlack Tree Node definition for leaf
 */
template<typename T>
RBTNode<T>::RBTNode()
        : color_(RBTColor::Black), lchild_(nullptr), rchild_(nullptr), parent_(nullptr), size(0){
}

template<typename T>
RBTNode<T>::RBTNode(RBTColor color, RBTNode* lchild, RBTNode* rchild, RBTNode* parent, T key)
        : color_(color),
          lchild_(lchild),
          rchild_(rchild),
          parent_(parent),
          key_(key),
          size(1){
}

/* Note: This redblack tree implemention not support multi same key tree nodes.
 * So make sure you can't insert a same key value node into this tree
 */ 
template<typename T>
class RedBlackTree{
 public:
    // basic constructor & deconstructor
    RedBlackTree();
    RedBlackTree(std::vector<T> key_array);
    ~RedBlackTree();

    // basic find & set operation
    const RBTNode<T>* getRoot() const;
    const RBTNode<T>* getNode(const T& key) const;
    bool DelTree(T key);

    // insert & delete operation
    bool Insert(const T& key);
    bool Delete(T key);

    // rank & select
    int Rank(const T& key);
    const RBTNode<T>* Select(int rank, const RBTNode<T>* root);

    // print operation
    void print();
    std::vector<T> OrderPass(std::string passway);

 private:
    RBTNode<T>* leaf_;
    RBTNode<T>* root_;
    RBTNode<T>* getNode_(const T& key) const;
    void DelTree_(RBTNode<T>* del_tree_root);
    bool LeftRotate_(RBTNode<T>* node_ptr);
    bool RightRotate_(RBTNode<T>* node_ptr);
    void InsertFixup_(RBTNode<T>* insert_item);
    void Transplant_(RBTNode<T>* old_tree, RBTNode<T>* new_tree, bool del = true);
    void DeleteFixup_(RBTNode<T>* delete_item);
    RBTNode<T>* Minimum(RBTNode<T>* root);
    void PreOrderPass_(RBTNode<T>* root, std::vector<T>& res);
    void InOrderPass_(RBTNode<T>* root, std::vector<T>& res);
    void PostOrderPass_(RBTNode<T>* root, std::vector<T>& res);
    int Rank_(RBTNode<T>* node);
};



/* RedBlack Tree Definition */

/* \brief default constructor
 */
template<typename T>
RedBlackTree<T>::RedBlackTree()
        : leaf_(new RBTNode<T>()), root_(leaf_){ 
}

/* \brief construct from a vector
 * param: vector of a key-based array
 */
template<typename T>
RedBlackTree<T>::RedBlackTree(std::vector<T> key_array)
        :leaf_(new RBTNode<T>()), root_(leaf_){
    if(root_)
        DelTree_(root_);
    for(auto e : key_array){
        if(!Insert(e))
            std::cout << "warning: key: " << e 
                      << " has existed in previous element. Ignore.\n"; 
    }
}

/* \brief deconstructor the class
 */
template<typename T>
RedBlackTree<T>::~RedBlackTree(){
    if(root_) DelTree_(root_);
    delete leaf_;
}

/* \brief get RedBlackTree root pointer
 * return: root handle (const RBTNode ptr)
 */
template<typename T>
const RBTNode<T>* RedBlackTree<T>::getRoot() const{
    return (const RBTNode<T>*)root_;
}

/* \brief find the tree node which has key value 'key'
 * param: node key value
 * return: const tree node pointer
 */
template<typename T>
const RBTNode<T>* RedBlackTree<T>::getNode(const T& key) const{
    auto node_ptr = getNode_(key);
    return (const RBTNode<T>*)node_ptr;
}

/* \brief delete a sub-tree(or entire tree) from redblack tree
 * param: sub tree root node key
 * return: true: deletion success; false: can't find the tree root
 */
template<typename T>
bool RedBlackTree<T>::DelTree(T key){
    RBTNode<T>* sub_tree_root = getNode(key);
    if(sub_tree_root == leaf_) return false;
    DelTree_(sub_tree_root);
    return true;
}

/* \brief find the tree node which has key value 'key'  --used for private
 * param: node key value
 * return: tree node pointer
 */
template<typename T>
RBTNode<T>* RedBlackTree<T>::getNode_(const T& key) const{
    auto iter = root_;
    while(iter != leaf_ && iter->key_ != key){
        if(key < iter->key_)
            iter = iter->lchild_;
        else
            iter = iter->rchild_;
    }
    return iter;
}

/* \brief delete a sub-tree(or entire tree) from redblack tree  --used for private
 * param: sub tree root node key
 */
template<typename T>
void RedBlackTree<T>::DelTree_(RBTNode<T>* del_tree_root){
    if(del_tree_root == leaf_) return;
    DelTree_(del_tree_root->lchild_);
    DelTree_(del_tree_root->rchild_);
    delete(del_tree_root);
    del_tree_root = nullptr;
}

/* \brief left rotate a node which has key_ = key     --used for private
 * param: key
 * return: true: success; false: rchild is nullptr
 */
template<typename T>
bool RedBlackTree<T>::LeftRotate_(RBTNode<T>* node_ptr){
    auto rchild = node_ptr->rchild_;
    if(rchild == leaf_) return false;
    // turn rchild's left subtree into node's right subtree
    node_ptr->rchild_ = rchild->lchild_;
    // set rchild's left subtree root parent prop
    if(rchild->lchild_ != leaf_)
        rchild->lchild_->parent_ = node_ptr;
    // set rchild's parent
    rchild->parent_ = node_ptr->parent_;
    // update root or node_ptr's parent
    if(rchild->parent_ == leaf_)
        root_ = rchild;
    else if(node_ptr == node_ptr->parent_->lchild_)
        node_ptr->parent_->lchild_ = rchild;
    else
        node_ptr->parent_->rchild_ = rchild;
    // update rchild's left subtree
    rchild->lchild_ = node_ptr;
    // update node_ptr's parent
    node_ptr->parent_ = rchild;
    // update size
    node_ptr->size = node_ptr->lchild_->size + node_ptr->rchild_->size + 1;
    rchild->size = rchild->lchild_->size + rchild->rchild_->size + 1;
    return true;
}

/* \brief right rotate a node which has key_ = key      --used for private
 * param: key
 * return: true: success; false: can't find key or lchild is nullptr
 */
template<typename T>
bool RedBlackTree<T>::RightRotate_(RBTNode<T>* node_ptr){
    auto lchild = node_ptr->lchild_;
    if(lchild == leaf_) return false;
    // turn lchild's right subtree into node's left subtee
    node_ptr->lchild_ = lchild->rchild_;
    // set lchild's right subtree root parent prop
    if(lchild->rchild_ != leaf_)
        lchild->rchild_->parent_ = node_ptr;
    // set lchild's parent
    lchild->parent_ = node_ptr->parent_;
    // update root or node_ptr's parent
    if(lchild->parent_ == leaf_)
        root_ = lchild;
    else if(node_ptr == node_ptr->parent_->lchild_)
        node_ptr->parent_->lchild_ = lchild;
    else
        node_ptr->parent_->rchild_ = lchild;
    // update lchild's right subtree
    lchild->rchild_ = node_ptr;
    // update node_ptr's parent
    node_ptr->parent_ = lchild;
    // update size
    node_ptr->size = node_ptr->lchild_->size + node_ptr->rchild_->size + 1;
    lchild->size = lchild->lchild_->size + lchild->rchild_->size + 1;
    return true;
}

/* \brief insert a new key into the redblack tree
 * param: key value
 * return: true: success; false: same key has already existed in rb tree
 */
template<typename T>
bool RedBlackTree<T>::Insert(const T& key){
    RBTNode<T>* y = leaf_;
    RBTNode<T>* x = root_;
    std::vector<RBTNode<T>* > path;
    while(x != leaf_){
        if(x->key_ == key) return false;
        path.push_back(x);
        y = x;
        if(key < x->key_)
            x = x->lchild_;
        else
            x = x->rchild_;
    }
    RBTNode<T>* z = new RBTNode<T>(RBTColor::Red, leaf_, leaf_, y, key);
    if(y == leaf_) 
        root_ = z;
    else if(z->key_ < y->key_)
        y->lchild_ = z;
    else
        y->rchild_ = z;
    // update path node's size
    if(!path.empty()){
        for(auto node : path)
            node->size += 1;
    }
    InsertFixup_(z);
    return true;
}


/* \brief fixup insert              -- used for private
 * param: insert redblack tree node pointer
 */
template<typename T>
void RedBlackTree<T>::InsertFixup_(RBTNode<T>* z){
    while(z->parent_->color_ == RBTColor::Red){
        if(z->parent_ == z->parent_->parent_->lchild_){
            auto y = z->parent_->parent_->rchild_;
            // case1 
            if(y->color_ == RBTColor::Red){
                z->parent_->color_ = RBTColor::Black;
                y->color_ = RBTColor::Black;
                y->parent_->color_ = RBTColor::Red;
                z = z->parent_->parent_;
            }
            // case2
            else if(z == z->parent_->rchild_){
                z = z->parent_;
                LeftRotate_(z);
            }
            // case3 
            else{
                z->parent_->color_ = RBTColor::Black;
                z->parent_->parent_->color_ = RBTColor::Red;
                RightRotate_(z->parent_->parent_);
            }
        }
        else{
            auto y = z->parent_->parent_->lchild_;
            // case1
            if(y->color_ == RBTColor::Red){
                z->parent_->color_ = RBTColor::Black;
                y->color_ = RBTColor::Black;
                y->parent_->color_ = RBTColor::Red;
                z = z->parent_->parent_;
            }
            // case2
            else if(z == z->parent_->lchild_){
                z = z->parent_;
                RightRotate_(z);
            }
            // case3
            else{
                z->parent_->color_ = RBTColor::Black;
                z->parent_->parent_->color_ = RBTColor::Red;
                LeftRotate_(z->parent_->parent_);
            }
        }
        if(!z->parent_) break;
    }
    root_->color_ = RBTColor::Black;
}

/* \brief print redblack tree
 */
template<typename T>
void RedBlackTree<T>::print(){
    if(root_ == leaf_){
        std::cout << "empty redblack tree" << std::endl;
        return;
    }
    std::queue<RBTNode<T>* > que;
    que.push(root_);
    std::size_t curr_layer_num = 1;
    std::size_t next_layer_num = 0;
    while(!que.empty()){
        auto tmp = que.front();
        que.pop();
        if(tmp->lchild_ != leaf_){
            std::cout << '/';
            que.push(tmp->lchild_);
            ++next_layer_num;
        }
        std::cout << tmp->key_ << '(' << (int)tmp->color_  << " | " << tmp->size << ')';
        if(tmp->rchild_ != leaf_){
            std::cout << '\\';
            que.push(tmp->rchild_);
            ++next_layer_num;
        }
        std::cout << '\t';
        --curr_layer_num;
        if(curr_layer_num == 0){
            std::cout << std::endl;
            curr_layer_num = next_layer_num;
            next_layer_num = 0;
        }
    }
}

/* \brief transplant an old tree by a new tree
 * param: old_tree: old subtree root; new_tree: new subtree root
 */
template<typename T>
void RedBlackTree<T>::Transplant_(RBTNode<T>* old_tree, RBTNode<T>* new_tree, bool del){
    if(old_tree->parent_ == leaf_)
        root_ = new_tree;
    else if(old_tree == old_tree->parent_->lchild_)
        old_tree->parent_->lchild_ = new_tree;
    else
        old_tree->parent_->rchild_ = new_tree;
    new_tree->parent_ = old_tree->parent_;
    if(del)
        DelTree_(old_tree);
}

/* \brief find the smallest key node of a subtree(tree)
 * param: subtree (entire tree) root
 * return: smallest key node pointer
 */
template<typename T>
RBTNode<T>* RedBlackTree<T>::Minimum(RBTNode<T>* root){
    auto res = root;
    while(res != leaf_ && res->lchild_ != leaf_){
        res = res->lchild_;
    }
    return res;
}

/* \brief delete a node which has specific key from redblack tree
 * param: key: deleted node's key
 * return: true: success; false: can't find key
 */
template<typename T>
bool RedBlackTree<T>::Delete(T key){
    auto node = getNode_(key);
    auto y = node;
    if(node == leaf_) return false;
    RBTColor orig_color = y->color_;
    RBTNode<T>* x = leaf_;
    // node doesn't have left subtree
    if(node->lchild_ == leaf_){
        // update size
        auto tmp = y;
        while(tmp != leaf_){
            tmp->size -= 1;
            tmp = tmp->parent_;
        }

        x = node->rchild_;
        if(x->rchild_ == leaf_)
            leaf_->parent_ = x;
        Transplant_(node, node->rchild_, false);
    }
    // node doesn't have right subtree
    else if(node->rchild_ == leaf_){
        // update size
        auto tmp = y;
        while(tmp != leaf_){
            tmp->size -= 1;
            tmp = tmp->parent_;
        }

        x = node->lchild_;
        if(x->lchild_ == leaf_)
            leaf_->parent_ = x;
        Transplant_(node, node->lchild_, false);
    }
    else{
        y = Minimum(node->rchild_);
        // update size
        auto tmp = y->parent_;
        while(tmp != leaf_){
            tmp->size -= 1;
            tmp = tmp->parent_;
        }
        y->size = node->size;
        // set color
        orig_color = y->color_;
        x = y->rchild_;
        if(x == leaf_)
            x->parent_ = y;
        if(y->parent_ != node){ 
            Transplant_(y, y->rchild_, false);
            y->rchild_ = node->rchild_;
            y->rchild_->parent_ = y;
        }
        Transplant_(node, y, false);
        y->lchild_ = node->lchild_;
        y->lchild_->parent_ = y;
        y->color_ = node->color_;
    }
    delete node;
    if(orig_color == RBTColor::Black)
        DeleteFixup_(x);
    return true;
}

template<typename T>
void RedBlackTree<T>::DeleteFixup_(RBTNode<T>* x){
    while(x!= root_ && x->color_ == RBTColor::Black){
        if(x == x->parent_->lchild_){
            auto w = x->parent_->rchild_;
            // case1
            if(w->color_ == RBTColor::Red){
                w->color_ = RBTColor::Black;
                x->parent_->color_ = RBTColor::Red;
                LeftRotate_(x->parent_);
                w = x->parent_->rchild_;
            }
            // case2
            if(w->lchild_ && w->lchild_->color_ == RBTColor::Black &&
               w->rchild_ && w->rchild_->color_ == RBTColor::Black){
                   w->color_ = RBTColor::Red;
                   x = x->parent_;
            }
            // case3
            else if(w->rchild_ && w->rchild_->color_ == RBTColor::Black){
                if(w->lchild_)
                    w->lchild_->color_ = RBTColor::Black;
                w->color_ = RBTColor::Red;
                RightRotate_(w);
                w = x->parent_->rchild_;
            }
            // case4
            else{
                w->color_ = x->parent_->color_;
                x->parent_->color_ = RBTColor::Black;
                w->rchild_->color_ = RBTColor::Black;
                LeftRotate_(w->parent_);
                x = root_;
            }
        }
        else{
            auto w = x->parent_->lchild_;
            // case1
            if(w->color_ == RBTColor::Red){
                w->color_ = RBTColor::Black;
                x->parent_->color_ = RBTColor::Red;
                RightRotate_(x->parent_);
                w = x->parent_->lchild_;
            }
            // case2
            if((w->lchild_ && w->lchild_->color_ == RBTColor::Black) &&
               (w->rchild_ && w->rchild_->color_ == RBTColor::Black)){
                   w->color_ = RBTColor::Red;
                   x = x->parent_;
            }
            // case3
            else if(w->lchild_ && w->lchild_->color_ == RBTColor::Black){
                if(w->rchild_)
                    w->rchild_->color_ = RBTColor::Black;
                w->color_ = RBTColor::Red;
                LeftRotate_(w);
                w = x->parent_->lchild_;
            }
            // case4
            else{
                w->color_ = x->parent_->color_;
                x->parent_->color_ = RBTColor::Black;
                w->lchild_->color_ = RBTColor::Black;
                RightRotate_(w->parent_);
                x = root_;
            }
        }
    }
    if(x) x->color_ = RBTColor::Black;
}

template<typename T>
std::vector<T> RedBlackTree<T>::OrderPass(std::string passway){
    std::vector<T> res;
    if(passway == std::string("preorder"))
        PreOrderPass_(root_, res);
    else if(passway == std::string("inorder"))
        InOrderPass_(root_, res);
    else if(passway == std::string("postorder"))
        PostOrderPass_(root_, res);
    else
        std::cout << "Please choose pass mode among: preorder, midorder, lastorder\n";
    return res;
}

template<typename T>
void RedBlackTree<T>::PreOrderPass_(RBTNode<T>* root, std::vector<T>& order){
    if(root == leaf_) return;
    order.push_back(root->key_);
    PreOrderPass_(root->lchild_, order);
    PreOrderPass_(root->rchild_, order);
}

template<typename T>
void RedBlackTree<T>::InOrderPass_(RBTNode<T>* root, std::vector<T>& order){
    if(root == leaf_) return;
    InOrderPass_(root->lchild_, order);
    order.push_back(root->key_);
    InOrderPass_(root->rchild_, order);
}

template<typename T>
void RedBlackTree<T>::PostOrderPass_(RBTNode<T>* root, std::vector<T>& order){
    if(root == leaf_) return;
    PostOrderPass_(root->lchild_, order);
    PostOrderPass_(root->rchild_, order);
    order.push_back(root->key_);
}

template<typename T>
int RedBlackTree<T>::Rank(const T& key){
    auto node = getNode(key);
    if(!node) return 0;
    return Rank_(node);
}

template<typename T>
int RedBlackTree<T>::Rank_(RBTNode<T>* node){
    int r = node->lchild_->size + 1;
    auto y = node;
    while(y != root_){
        if(y == y->parent_->rchild_)
            r += y->parent_->lchild_->size + 1;
        y = y->parent_;
    }
    return r;
}

template<typename T>
const RBTNode<T>* RedBlackTree<T>::Select(int rank, const RBTNode<T>* root){
    int r = root->lchild_->size + 1;
    if(rank == r)
        return root;
    else if(rank < r)
        return Select(rank, root->lchild_);
    else
        return Select(rank - r, root->rchild_);
}
