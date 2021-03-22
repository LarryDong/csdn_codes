// Test pointcloud copy.

#include <iostream>
#include <string>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

using namespace std;

typedef pcl::PointXYZ MyPoint;
typedef pcl::PointCloud<MyPoint> MyPointCloud;

void func_ptr(MyPointCloud::Ptr pc){
    pc->resize(0);
}

void func_pointcloud(MyPointCloud pc){
    pc.resize(0);
}

void func_ref(MyPointCloud& pc){
    pc.resize(10);
}

void func_pointcloud_ref(const MyPointCloud& pc){
    // Error! cannot change size.
    // pc.resize(0); 
    ;
}



int main(void){

    MyPointCloud::Ptr pc (new MyPointCloud()), pc2(new MyPointCloud());
    MyPointCloud pc3, pc4;

    cout<<"================  Function test ================" <<endl;
    string filename = "mesh.pcd";
    pcl::io::loadPCDFile<MyPoint>(filename, *pc);

    cout << "------- Test 1. Using Ptr" << endl;
    cout<<"before: "<< (*pc).size() << endl;
    func_ptr(pc);
    cout << "after: " << (*pc).size() << endl;

    pcl::io::loadPCDFile<MyPoint>(filename, *pc);
    cout << "------- Test 2.1 Using pointcloud but input *ptr" << endl;
    cout<<"before: "<< (*pc).size() << endl;
    func_pointcloud(*pc);
    cout << "after: " << (*pc).size() << endl;

    pcl::io::loadPCDFile<MyPoint>(filename, pc3);
    cout << "------- Test 2.2 Using pointcloud but input pointcloud" << endl;
    cout<<"before: "<< pc3.size() << endl;
    func_pointcloud(pc3);
    cout << "after: " << pc3.size() << endl;

    pcl::io::loadPCDFile<MyPoint>(filename, pc3);
    pcl::io::loadPCDFile<MyPoint>(filename, *pc);
    cout << "------- Test 3. Using ref pointcloud" << endl;
    cout<<"before: "<< (*pc).size() << endl;
    func_ref(*pc);
    cout << "after: " << (*pc).size() << endl;
    cout<<"before: "<< pc3.size() << endl;
    func_ref(pc3);
    cout << "after: " << pc3.size() << endl;


    cout << "================  Operator= test ================" << endl;
    cout << "------- Test 1. Copy pointer to pointer" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, *pc);
    pc2 = pc;
    cout << "Pc2: " << pc2->size() << endl;
    pc->resize(0);
    cout << "Pc2: " << pc2->size() << endl;

    cout << "------- Test 2. Copy *pointer to *pointer" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, *pc);
    *pc2 = *pc;
    cout << "Pc2: " << pc2->size() << endl;
    pc->resize(0);
    cout << "Pc2: " << pc2->size() << endl;

    cout << "------- Test 3. Copy *pointer to value" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, *pc);
    pc3 = *pc;
    cout << "Pc3: " << pc3.size() << endl;
    pc->resize(0);
    cout << "Pc3: " << pc3.size() << endl;


    cout << "------- Test 4. Copy value to value" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, pc3);
    pc4 = pc3;
    cout << "Pc4: " << pc3.size() << endl;
    pc3.resize(0);
    cout << "Pc4: " << pc3.size() << endl;

    cout << "------- Test 5. Copy value to *pointer" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, pc3);
    *pc = pc3;
    cout << "Pc: " << pc->size() << endl;
    pc3.resize(0);
    cout << "Pc: " << pc->size() << endl;


    cout << "================  Copy Function test ================" << endl;
    cout << "------- Test 1. Copy *pointer to *pointer" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, *pc);
    pcl::copyPointCloud(*pc, *pc2);
    cout << "pc2: " << pc2->size() << endl;
    pc->resize(0);
    cout << "pc2: " << pc2->size() << endl;

    cout << "------- Test 2. Copy *pointer to value" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, *pc);
    pcl::copyPointCloud(*pc, pc3);
    cout << "pc3: " << pc3.size() << endl;
    pc->resize(0);
    cout << "pc3: " << pc3.size() << endl;

    cout << "------- Test 3. Copy value to *pointer" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, pc3);
    pcl::copyPointCloud(pc3, *pc);
    cout << "pc: " << pc->size() << endl;
    pc3.resize(0);
    cout << "pc: " << pc->size() << endl;

    cout << "------- Test 4. Copy value to value" << endl;
    pcl::io::loadPCDFile<MyPoint>(filename, pc3);
    pcl::copyPointCloud(pc3, pc4);
    cout << "pc4: " << pc4.size() << endl;
    pc3.resize(0);
    cout << "pc4: " << pc4.size() << endl;
    return 0;
}
