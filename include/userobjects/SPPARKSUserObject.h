#ifndef SPPARKSUSEROBJECT_H
#define SPPARKSUSEROBJECT_H

#include "GeneralUserObject.h"
#include "MooseMesh.h"

#include "spparks/src/library.h"

// forward declarations
class SPPARKSUserObject;

template<>
InputParameters validParams<SPPARKSUserObject>();

class SPPARKSUserObject : public GeneralUserObject
{
public:
  SPPARKSUserObject(const InputParameters & parameters);
  virtual ~SPPARKSUserObject();

  virtual void initialSetup();
  virtual void residualSetup() {}
  virtual void timestepSetup() {}

  virtual void initialize();
  virtual void execute();
  virtual void finalize() {}

  int  getIntValue(unsigned fem_node_id, unsigned int index) const;
  Real getDoubleValue(unsigned fem_node_id, unsigned int index) const;

protected:
  struct FEMID;
  typedef FEMID SPPARKSID;

  void initSPPARKS();

  char * runSPPARKSCommand(const std::string & cmd);

  Real getSPPARKSTime(Real dt) { return dt / _time_ratio; }

  template <typename T>
  Real getValue(const std::map<unsigned int, std::map<unsigned int, T> > & data, unsigned fem_node_id, unsigned int index) const;

  template <typename T>
  void getSPPARKSDataPointer(T *& ptr, const std::string & name, unsigned int index);

  template <typename T>
  void getSPPARKSPointer(T *& ptr, const std::string & name) const;

  void getSPPARKSData();
  void setSPPARKSData();

  template <typename T>
  void getSPPARKSData(std::map<unsigned int, T> & storage, const std::string & name, unsigned int index);

  template <typename T>
  void sendRecvSPPARKSData(const T * const data, std::map<unsigned int, T> & storage);

  template <typename T>
  void setSPPARKSData(T * data, const std::string & name, unsigned int index, MooseVariable & var);

  // Initiate MOOSE based on data from SPPARKS, added by YF.
  void setFEMData();

  template <typename T>
  void setFEMData(const std::string & name, unsigned int index, MooseVariable & var);

  template <typename T>
  void sendRecvFEMData(const std::map<libMesh::dof_id_type, T> & storage, T * const data);

  /// SPPARKS instance pointer
  void * _spparks;

  const std::string & _file;
  const bool _spparks_only;
  const std::vector<unsigned int> _from_ivar;
  const std::vector<unsigned int> _from_dvar;
  const std::vector<unsigned int> _to_ivar;
  const std::vector<unsigned int> _to_dvar;
  const Real _xmin;
  const Real _ymin;
  const Real _zmin;
  const Real _xmax;
  const Real _ymax;
  const Real _zmax;
  bool _init_spparks;
  const Real _time_ratio;
  bool _initialized;

  // added by YF, do one time SPPARKS run
  bool _one_time_run;
  int _n_spparks_run;

  int _dim;

  std::vector<MooseVariable*> _int_vars;
  std::vector<MooseVariable*> _double_vars;
  std::vector<MooseVariable*> _sol_vars; //added by YF

  //
  // Communication maps
  //

  /// SPPARKSID to vector of procs that need the value
  std::map<SPPARKSID, std::vector<unsigned int> > _spparks_to_proc;
  /// Processor to list of MOOSE FEM ids
  std::map<unsigned int, std::vector<libMesh::dof_id_type> > _sending_proc_to_fem_id;
  /// FEMID to vector of procs that need the value
  std::map<FEMID, std::vector<unsigned int> > _fem_to_proc;
  /// Processor to list of SPPARKS ids
  std::map<unsigned int, std::vector<unsigned int> > _sending_proc_to_spparks_id;

  unsigned _num_local_fem_nodes;
  unsigned _num_local_spparks_nodes;

  /// Local SPPARKSID to local FEMID
  std::map<SPPARKSID, FEMID> _spparks_to_fem;

  /// Local FEMID to local SPPARKSID
  std::multimap<FEMID, SPPARKSID> _fem_to_spparks;

  /// Maps from variable index to MOOSE FEM node id to value
  std::map<unsigned int, std::map<unsigned int, int> > _int_data_for_fem;
  std::map<unsigned int, std::map<unsigned int, double> > _double_data_for_fem;

  // Maps from variable index to value (vector index is array index)
  std::map<unsigned int, std::vector<int> > _int_data_for_spparks;
  std::map<unsigned int, std::vector<double> > _double_data_for_spparks;

  Real _last_time;
};

struct SPPARKSUserObject::FEMID
{
  FEMID(libMesh::dof_id_type ident, const Point & p) :
    id(ident), coor(p)
  {
  }

  libMesh::dof_id_type id;
  Point coor;

  // comparison operator for use in maps
  bool operator<(const FEMID & rhs) const
  {
    // return coor < rhs.coor;
    const Real tol = 1e-12;

    if (!fuzzyEqual(coor(0), rhs.coor(0), tol))
      return (coor(0) + tol) < rhs.coor(0);

    if (!fuzzyEqual(coor(1), rhs.coor(1), tol))
      return (coor(1) + tol) < rhs.coor(1);

    return (coor(2) + tol) < rhs.coor(2);
  }

private:
  bool fuzzyEqual(Real f, Real s, Real tol) const
  {
    return f < (s+tol) && (f > s-tol);
  }
};

template <typename T>
Real
SPPARKSUserObject::getValue(const std::map<unsigned int, std::map<unsigned int, T> > & data, unsigned int fem_node_id, unsigned int index) const
{
  // Extract the data
  const typename std::map<unsigned int, std::map<unsigned int, T> >::const_iterator it = data.find(index);
  if (it == data.end())
    mooseError("SPPARKSUserObject error: unknown index " << index);

  const typename std::map<unsigned int, T>::const_iterator it2 = it->second.find(fem_node_id);
  if (it2 == it->second.end())
  {
    mooseWarning("SPPARKSUserObject error: unknown MOOSE FEM node id " << fem_node_id);
    return 0;
  }

  return it2->second;
}

template <typename T>
void
SPPARKSUserObject::getSPPARKSDataPointer(T *& ptr, const std::string & name, unsigned int index)
{
  std::stringstream fullname;
  fullname << name;
  fullname << index;
  getSPPARKSPointer(ptr, fullname.str().c_str());
}

template <typename T>
void
SPPARKSUserObject::getSPPARKSPointer(T *& ptr, const std::string & name) const
{
  void * p = spparks_extract(_spparks, name.c_str());
  if (!p)
    mooseError("SPPARKS returned NULL pointer for " << name);
  ptr = static_cast<T*>(p);
}

template <typename T>
void
SPPARKSUserObject::getSPPARKSData(std::map<unsigned int, T> & storage, const std::string & name, unsigned int index)
{
  T * data;
  getSPPARKSDataPointer(data, name.c_str(), index);

  // Copy data from local SPPARKS node to local MOOSE FEM node
  // Index into storage is MOOSE FEM node id.
  for (std::multimap<FEMID, SPPARKSID>::const_iterator i = _fem_to_spparks.begin(); i != _fem_to_spparks.end(); ++i)
    storage[i->first.id] = data[i->second.id];

  // Copy data across processors
  if (n_processors() > 1)
    sendRecvSPPARKSData(data, storage);
}

template <typename T>
void
SPPARKSUserObject::sendRecvSPPARKSData(const T * const data, std::map<unsigned int, T> & storage)
{
  Parallel::MessageTag comm_tag(101);

  const unsigned num_recvs = _sending_proc_to_fem_id.size();
  std::vector<Parallel::Request> recv_request(num_recvs);

  std::map<unsigned int, std::vector<T> > data_to_me; // sending proc, vector of SPPARKS values (one value per SPPARKS node)
  unsigned offset = 0;
  for (std::map<unsigned int, std::vector<libMesh::dof_id_type> >::const_iterator i = _sending_proc_to_fem_id.begin();
       i != _sending_proc_to_fem_id.end(); ++i)
  {
    data_to_me[i->first].resize(i->second.size());
    _communicator.receive(i->first, data_to_me[i->first], recv_request[offset], comm_tag);
    ++offset;
  }

  std::map<unsigned int, std::vector<T> > data_from_me; // Processor, list of SPPARKS values
  for (auto & procs : _spparks_to_proc)
    for (auto & proc : procs.second)
      data_from_me[proc].push_back(data[procs.first.id]);

  for (auto & data : data_from_me)
    _communicator.send(data.first, data.second, comm_tag);

  Parallel::wait(recv_request);

  // Move data into storage
  for (std::map<unsigned int, std::vector<libMesh::dof_id_type> >::const_iterator i = _sending_proc_to_fem_id.begin();
       i != _sending_proc_to_fem_id.end(); ++i)
  {
    const std::vector<libMesh::dof_id_type> & id = i->second;
    const std::vector<T> & v = data_to_me[i->first];

    // storage is MOOSE FEM node id, value
    for (unsigned j = 0; j < v.size(); ++j)
      storage[id[j]] = v[j];
  }
}

template <typename T>
void
SPPARKSUserObject::setSPPARKSData(T * data, const std::string & name, unsigned int index, MooseVariable & var)
{
  getSPPARKSDataPointer(data, name, index);

  SystemBase & sys = var.sys();
  NumericVector<Number> & solution = sys.solution();

  // Extract MOOSE data
  std::map<libMesh::dof_id_type, T> fem_data;
  ConstNodeRange & node_range = *_fe_problem.mesh().getLocalNodeRange();
  for (ConstNodeRange::const_iterator i = node_range.begin(); i < node_range.end(); ++i)
  {
    // Get data
    const Real value = solution((*i)->dof_number(sys.number(), var.number(), 0));

    fem_data[(*i)->id()] = value;
  }

  // Index into data is SPPARKS node id.
  for (std::multimap<FEMID, SPPARKSID>::const_iterator i = _fem_to_spparks.begin(); i != _fem_to_spparks.end(); ++i)
    data[i->second.id] = fem_data[i->first.id];

  // Copy data across processors
  if (n_processors() > 1)
    sendRecvFEMData(fem_data, data);
}

template <typename T>
void
SPPARKSUserObject::setFEMData(const std::string & name, unsigned int index, MooseVariable & var)
{
  // get SPPARKS data
  std::map<unsigned int, T> spparks_data;
  getSPPARKSData(spparks_data, name, index);

  SystemBase & sys = var.sys();
  NumericVector<Number> & solution = sys.solution();

  // Extract MOOSE data
  ConstNodeRange & node_range = *_fe_problem.mesh().getLocalNodeRange();

  // Set data
  for (ConstNodeRange::const_iterator i = node_range.begin(); i < node_range.end(); ++i)
    solution.set((*i)->dof_number(sys.number(), var.number(), 0), spparks_data[(*i)->id()]);

  solution.close();
}

// template <typename T>
// void
// SPPARKSUserObject::setFEMData(T * data, const std::string & name, unsigned int index, MooseVariable & var)
// {
//   getSPPARKSDataPointer(data, name, index);
//
//   SystemBase & sys = var.sys();
//   NumericVector<Number> & solution = sys.solution();
//
//   // Extract MOOSE data
//   std::map<libMesh::dof_id_type, T> spparks_data;
//   ConstNodeRange & node_range = *_fe_problem.mesh().getLocalNodeRange();
//
//   // Index into data is SPPARKS node id.
//   for (std::multimap<FEMID, SPPARKSID>::const_iterator i = _spparks_to_fem.begin(); i != _spparks_to_fem.end(); ++i)
//     spparks_data[i->first.id] = data[i->second.id];
//
//   // set data
//   for (ConstNodeRange::const_iterator i = node_range.begin(); i < node_range.end(); ++i)
//     solution.set((*i)->dof_number(sys.number(), var.number(), 0), spparks_data[(*i)->id()]);
//
//   // Copy data across processors
//   if (n_processors() > 1)
//     sendRecvSPPARKSData(data, spparks_data);
// }

template <typename T>
void
SPPARKSUserObject::sendRecvFEMData(const std::map<libMesh::dof_id_type, T> & storage, T * const data)
{
  Parallel::MessageTag comm_tag(101);

  const unsigned num_recvs = _sending_proc_to_spparks_id.size();
  std::vector<Parallel::Request> recv_request(num_recvs);

  // sending proc, vector of MOOSE values (one value per MOOSE FEM node)
  std::map<unsigned int, std::vector<T> > data_to_me;
  unsigned offset = 0;
  for (std::map<unsigned int, std::vector<unsigned int> >::const_iterator i = _sending_proc_to_spparks_id.begin();
       i != _sending_proc_to_spparks_id.end(); ++i)
  {
    data_to_me[i->first].resize(i->second.size());
    _communicator.receive(i->first, data_to_me[i->first], recv_request[offset], comm_tag);
    ++offset;
  }

  std::map<unsigned int, std::vector<T> > data_from_me; // Processor, list of MOOSE values
  for (std::map<FEMID, std::vector<unsigned int> >::const_iterator i = _fem_to_proc.begin(); i != _fem_to_proc.end(); ++i)
  {
    for (unsigned j = 0; j < i->second.size(); ++j)
      data_from_me[i->second[j]].push_back(storage.find(i->first.id)->second);
  }

  for (typename std::map<unsigned int, std::vector<T> >::const_iterator i = data_from_me.begin(); i != data_from_me.end(); ++i)
    _communicator.send(i->first, data_from_me[i->first], comm_tag);

  Parallel::wait(recv_request);

  // Move data into storage
  for (std::map<unsigned int, std::vector<unsigned int> >::const_iterator i = _sending_proc_to_spparks_id.begin();
       i != _sending_proc_to_spparks_id.end(); ++i)
  {
    const std::vector<unsigned int> & id = i->second;
    const std::vector<T> & v = data_to_me[i->first];
    if (id.size() != v.size())
      mooseError("Mismatched communication vectors");

    // data is SPPARKS index, value
    for (unsigned j = 0; j < v.size(); ++j)
      data[id[j]] = v[j];
  }
}

#endif
