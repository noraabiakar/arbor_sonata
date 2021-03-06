#pragma once

#include <iostream>
#include <string>

#include <hdf5.h>

#include "sonata_excpetions.hpp"

#define MAX_NAME 1024

class h5_dataset {
private:
    hid_t parent_id_;
    std::string name_;
    size_t size_;

public:
    h5_dataset(hid_t parent, std::string name): parent_id_(parent), name_(name) {
        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);
        hid_t dspace = H5Dget_space(id_);

        const int ndims = H5Sget_simple_extent_ndims(dspace);

        hsize_t dims[ndims];
        H5Sget_simple_extent_dims(dspace, dims, NULL);

        size_ = dims[0];

        H5Dclose(id_);
    }

    std::string name() {
        return name_;
    }

    int size() {
        return size_;
    }

    auto int_at(const int i) {
        const hsize_t idx = (hsize_t)i;

        // Output
        int *out = new int[1];

        // Output dimensions 1x1
        hsize_t dims = 1;
        hsize_t dim_sizes[] = {1};

        // Output size
        hsize_t num_elements = 1;

        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);
        hid_t dspace = H5Dget_space(id_);

        H5Sselect_elements(dspace, H5S_SELECT_SET, num_elements, &idx);

        hid_t out_mem = H5Screate_simple(dims, dim_sizes, NULL);

        auto status = H5Dread(id_, H5T_NATIVE_INT, out_mem, dspace, H5P_DEFAULT, out);

        H5Sclose(dspace);
        H5Sclose(out_mem);
        H5Dclose(id_);

        if (status < 0 ) {
            throw sonata_dataset_exception(name_, (unsigned)i);
        }

        int r = out[0];
        delete [] out;

        return r;
    }

    auto double_at(const int i) {
        const hsize_t idx = (hsize_t)i;

        // Output
        double *out = new double[1];

        // Output dimensions 1x1
        hsize_t dims = 1;
        hsize_t dim_sizes[] = {1};

        // Output size
        hsize_t num_elements = 1;

        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);
        hid_t dspace = H5Dget_space(id_);

        H5Sselect_elements(dspace, H5S_SELECT_SET, num_elements, &idx);
        hid_t out_mem = H5Screate_simple(dims, dim_sizes, NULL);

        auto status = H5Dread(id_, H5T_NATIVE_DOUBLE, out_mem, dspace, H5P_DEFAULT, out);

        H5Sclose(dspace);
        H5Sclose(out_mem);
        H5Dclose(id_);

        if (status < 0) {
            throw sonata_dataset_exception(name_, (unsigned)i);
        }

        double r = out[0];
        delete [] out;

        return r;
    }

    auto string_at(const int i) {
        const hsize_t idx = (hsize_t)i;

        // Output
        char *out = new char[1];

        // Output dimensions 1x1
        hsize_t dims = 1;
        hsize_t dim_sizes[] = {1};

        // Output size
        hsize_t num_elements = 1;

        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);
        hid_t dspace = H5Dget_space(id_);

        H5Sselect_elements(dspace, H5S_SELECT_SET, num_elements, &idx);
        hid_t out_mem = H5Screate_simple(dims, dim_sizes, NULL);

        auto status = H5Dread(id_, H5T_NATIVE_CHAR, out_mem, dspace, H5P_DEFAULT, out);

        H5Sclose(dspace);
        H5Sclose(out_mem);
        H5Dclose(id_);

        if (status < 0) {
            throw sonata_dataset_exception(name_, (unsigned)i);
        }

        int r = out[0];
        delete [] out;

        return r;
    }

    auto int_range(const int i, const int j) {
        hsize_t offset = i;
        hsize_t count = j-i;
        hsize_t stride = 1;
        hsize_t  block = 1;
        hsize_t dimsm = count;

        int rdata[count];

        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);
        hid_t dspace = H5Dget_space(id_);

        hid_t out_mem = H5Screate_simple(1, &dimsm, NULL);

        H5Sselect_hyperslab(dspace, H5S_SELECT_SET, &offset, &stride, &count, &block);
        auto status = H5Dread(id_, H5T_NATIVE_INT, out_mem, dspace, H5P_DEFAULT, rdata);

        H5Sclose(dspace);
        H5Sclose(out_mem);
        H5Dclose(id_);

        if (status < 0) {
            throw sonata_dataset_exception(name_, (unsigned)i, (unsigned)j);
        }

        std::vector<int> out(rdata, rdata + count);

        return out;
    }

    auto double_range(const int i, const int j) {
        hsize_t offset = i;
        hsize_t count = j-i;
        hsize_t stride = 1;
        hsize_t  block = 1;
        hsize_t dimsm = count;

        double rdata[count];

        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);
        hid_t dspace = H5Dget_space(id_);

        hid_t out_mem = H5Screate_simple(1, &dimsm, NULL);

        H5Sselect_hyperslab(dspace, H5S_SELECT_SET, &offset, &stride, &count, &block);

        auto status = H5Dread(id_, H5T_NATIVE_DOUBLE, out_mem, dspace, H5P_DEFAULT, rdata);

        H5Sclose(dspace);
        H5Sclose(out_mem);
        H5Dclose(id_);

        if (status < 0) {
            throw sonata_dataset_exception(name_, (unsigned)i, (unsigned)j);
        }

        std::vector<double> out(rdata, rdata + count);

        return out;
    }

    auto int_pair_at(const int i) {
        const hsize_t idx_0[2] = {(hsize_t)i, (hsize_t)0};

        // Output
        int out_0, out_1;

        // Output dimensions 1x1
        hsize_t dims = 1;
        hsize_t dim_sizes[] = {1};

        // Output size
        hsize_t num_elements = 1;

        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);
        hid_t dspace = H5Dget_space(id_);

        H5Sselect_elements(dspace, H5S_SELECT_SET, num_elements, idx_0);
        hid_t out_mem_0 = H5Screate_simple(dims, dim_sizes, NULL);

        auto status0 = H5Dread(id_, H5T_NATIVE_INT, out_mem_0, dspace, H5P_DEFAULT, &out_0);

        const hsize_t idx_1[2] = {(hsize_t)i, (hsize_t)1};

        H5Sselect_elements(dspace, H5S_SELECT_SET, num_elements, idx_1);
        hid_t out_mem_1 = H5Screate_simple(dims, dim_sizes, NULL);

        auto status1 = H5Dread(id_, H5T_NATIVE_INT, out_mem_1, dspace, H5P_DEFAULT, &out_1);

        H5Sclose(dspace);
        H5Sclose(out_mem_0);
        H5Sclose(out_mem_1);
        H5Dclose(id_);

        if (status0 < 0 || status1 < 0) {
            throw sonata_dataset_exception(name_, (unsigned)i);
        }

        return std::make_pair(out_0, out_1);
    }

    auto int_1d() {
        int out_a[size_];
        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);

        auto status = H5Dread(id_, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT,
                out_a);
        H5Dclose(id_);

        if (status < 0) {
            throw sonata_dataset_exception(name_);
        }

        std::vector<int> out(out_a, out_a + size_);

        return out;
    }

    auto int_2d() {
        int out_a[size_][2];
        auto id_ = H5Dopen(parent_id_, name_.c_str(), H5P_DEFAULT);

        auto status = H5Dread(id_, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, out_a);

        H5Dclose(id_);

        if (status < 0) {
            throw sonata_dataset_exception(name_);
        }

        std::vector<std::pair<int, int>> out(size_);
        for (unsigned i = 0; i < size_; i++) {
            out[i] = std::make_pair(out_a[i][0], out_a[i][1]);
        }

        return out;
    }
};

class h5_group {
private:
    struct group_handle {
        group_handle(hid_t parent_id, std::string name): id(H5Gopen(parent_id, name.c_str(), H5P_DEFAULT)), name(name){}
        ~group_handle() {
            H5Gclose(id);
        }
        hid_t id;
        std::string name;
    };

    hid_t parent_id_;
    std::string name_;
    group_handle group_h_;

public:
    std::vector<std::shared_ptr<h5_group>> groups_;
    std::vector<std::shared_ptr<h5_dataset>> datasets_;

    h5_group(hid_t parent, std::string name): parent_id_(parent), name_(name), group_h_(parent_id_, name_) {

        hsize_t nobj;
        H5Gget_num_objs(group_h_.id, &nobj);

        char memb_name[MAX_NAME];

        groups_.reserve(nobj);

        for (unsigned i = 0; i < nobj; i++) {
            H5Gget_objname_by_idx(group_h_.id, (hsize_t)i, memb_name, (size_t)MAX_NAME);
            hid_t otype = H5Gget_objtype_by_idx(group_h_.id, (size_t)i);
            if (otype == H5G_GROUP) {
                groups_.emplace_back(std::make_shared<h5_group>(group_h_.id, memb_name));
            }
            else if (otype == H5G_DATASET) {
                datasets_.emplace_back(std::make_shared<h5_dataset>(group_h_.id, memb_name));
            }
        }
    }

    std::string name() {
        return name_;
    }
};

class h5_file {
private:
    struct file_handle {
        file_handle(std::string file): id(H5Fopen(file.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT)), name(file) {}
        ~file_handle() {
            H5Fclose(id);
        }
        hid_t id;
        std::string name;
    };

    std::string file_;
    file_handle file_h_;

public:
    void print() {
        std::cout << top_group_->name() << std::endl;
        for (auto g0: top_group_->groups_) {
            std::cout << "\t" << g0->name() << std::endl;
            for (auto g1: g0->groups_) {
                std::cout << "\t\t" << g1->name() << std::endl;
                for (auto g2: g1->groups_) {
                    std::cout << "\t\t\t" << g2->name() << std::endl;
                    for (auto g3: g2->groups_) {
                        std::cout << "\t\t\t\t" << g3->name() << std::endl;
                        for (auto g4: g3->groups_) {
                            std::cout << "\t\t\t\t\t" << g4->name() << std::endl;
                        }
                        for (auto d4: g3->datasets_) {
                            std::cout << "\t\t\t\t\t" << d4->name() << " " << d4->size() << std::endl;
                        }
                    }
                    for (auto d3: g2->datasets_) {
                        std::cout << "\t\t\t\t" << d3->name() << " " << d3->size() << std::endl;
                    }
                }
                for (auto d2: g1->datasets_) {
                    std::cout << "\t\t\t" << d2->name() << " " << d2->size() << std::endl;
                }
            }
            for (auto d1: g0->datasets_) {
                std::cout << "\t\t" << d1->name() << " " << d1->size() << std::endl;
            }
        }
        for (auto d0: top_group_->datasets_) {
            std::cout << "\t" << d0->name() << " " << d0->size() << std::endl;
        }
    }

    std::shared_ptr<h5_group> top_group_;
    h5_file(std::string name):
            file_(name),
            file_h_(name),
            top_group_(std::make_shared<h5_group>(file_h_.id, "/")) {}

    std::string name() {
        return file_;
    }
};

///////////////////////////////////////////////////////////

class h5_wrapper {
public:
    h5_wrapper() {}

    h5_wrapper(const std::shared_ptr<h5_group>& g): ptr(g) {
        unsigned i = 0;
        for (auto d: ptr->datasets_) {
            dset_map[d->name()] = i++;
        }
        i = 0;
        for (auto g: ptr->groups_) {
            member_map[g->name()] = i++;
            members.emplace_back(g);
        }
    }

    int size() {
        return members.size();
    }

    int find_group(std::string name) {
        if (member_map.find(name) != member_map.end()) {
            return member_map[name];
        }
        return -1;
    }

    int find_dataset(std::string name) {
        if (dset_map.find(name) != dset_map.end()) {
            return dset_map[name];
        }
        return -1;
    }

    int int_at(std::string name, unsigned i) {
        if (find_dataset(name) != -1) {
            return ptr->datasets_[dset_map[name]]->int_at(i);
        }
        throw sonata_dataset_exception(name);
    }

    double double_at(std::string name, unsigned i) {
        if (find_dataset(name) != -1) {
            return ptr->datasets_[dset_map[name]]->double_at(i);
        }
        throw sonata_dataset_exception(name);
    }

    std::string string_at(std::string name, unsigned i) {
        if (find_dataset(name) != -1) {
            return std::to_string(ptr->datasets_[dset_map[name]]->string_at(i));
        }
        throw sonata_dataset_exception(name);
    }

    std::vector<int> int_range(std::string name, unsigned i, unsigned j) {
        if (find_dataset(name)!= -1) {
            if (j - i > 1) {
                return ptr->datasets_[dset_map[name]]->int_range(i, j);
            } else {
                return {ptr->datasets_[dset_map[name]]->int_at(i)};
            }
        }
        throw sonata_dataset_exception(name);
    }

    std::vector<double> double_range(std::string name, unsigned i, unsigned j) {
        if (find_dataset(name)!= -1) {
            return ptr->datasets_[dset_map[name]]->double_range(i, j);
        }
        throw sonata_dataset_exception(name);
    }

    std::pair<int, int> int_pair_at(std::string name, unsigned i) {
        if (find_dataset(name)!= -1) {
            return ptr->datasets_[dset_map[name]]->int_pair_at(i);
        }
        throw sonata_dataset_exception(name);
    }

    std::vector<int> int_1d(std::string name) {
        if (find_dataset(name)!= -1) {
            return ptr->datasets_[dset_map[name]]->int_1d();
        }
        throw sonata_dataset_exception(name);
    }

    std::vector<std::pair<int, int>> int_2d(std::string name) {
        if (find_dataset(name)!= -1) {
            return ptr->datasets_[dset_map[name]]->int_2d();
        }
        throw sonata_dataset_exception(name);
    }

    h5_wrapper operator [](unsigned i) const {
        if (i < members.size() && i >= 0) {
            return members[i];
        }
        throw sonata_exception("h5_wrapper index out of range");
    }

    std::string name() {
        return ptr->name();
    }

private:
    std::shared_ptr<h5_group> ptr;
    std::vector<h5_wrapper> members;
    std::unordered_map<std::string, unsigned> dset_map;
    std::unordered_map<std::string, unsigned> member_map;
};


class hdf5_record {
public:
    hdf5_record(const std::shared_ptr<h5_file>& file) {
        if (file->top_group_->groups_.size() != 1) {
            throw sonata_exception("file hierarchy wrong\n");
        }

        unsigned idx = 0;
        for (auto g: file->top_group_->groups_.front()->groups_) {
            map_[g->name()] = idx++;
            populations_.emplace_back(g);
        }

        partition_.push_back(0);
        for (auto& p: file->top_group_->groups_.front()->groups_) {
            for(auto& d: p->datasets_) {
                if (d->name().find("type_id") != std::string::npos) {
                    num_elements_ += d->size();
                    partition_.push_back(num_elements_);
                }
            }
        }
    }

    void verify_edges() {
        for (auto& p: populations()) {
            if (p.find_group("indicies") == -1) {
                throw sonata_exception("indicies group must be available in all edge population groups ");
            }
            if (p.find_dataset("edge_type_id") == -1) {
                throw sonata_exception("edge_type_id dataset not provided in edge populations");
            }
            if (p.find_dataset("edge_id") != -1) {
                throw sonata_exception("edge_id datasets not supported; "
                                            "ids are automatically assigned contiguously starting from 0");
            }
        }
    }

    void verify_nodes() {
        for (auto& p: populations()) {
            if (p.find_dataset("node_type_id") == -1) {
                throw sonata_exception("node_type_id dataset not provided in node populations");
            }
            if (p.find_dataset("node_id") != -1) {
                throw sonata_exception("node_id datasets not supported; "
                                            "ids are automatically assigned contiguously starting from 0");
            }
        }
    }

    int num_elements() {
        return num_elements_;
    }

    h5_wrapper operator [](int i) const {
        return populations_[i];
    }

    std::vector<h5_wrapper> populations() {
        return populations_;
    }

    std::vector<unsigned> partitions() {
        return partition_;
    }

    std::unordered_map<std::string, unsigned> map() {
        return map_;
    }

private:
    int num_elements_ = 0;
    std::vector<unsigned> partition_;
    std::vector<h5_wrapper> populations_;
    std::unordered_map<std::string, unsigned> map_;
};
