#include "UHH2/common/include/TopPtReweight.h"

#include "boost/algorithm/string.hpp"

using namespace std;
using namespace uhh2;

TopPtReweight::TopPtReweight(uhh2::Context& ctx,
			     float a, float b,
			     const std::string& ttgen_name,
			     const std::string& weight_name,
			     bool apply_weight,
			     double norm_factor):
  a_(a), b_(b),
  h_pt_rew_weight_(ctx.declare_event_output<float>("weight_pt_rew")),
  h_pt_rew_weight_down_(ctx.declare_event_output<float>("weight_pt_rew_down")),
  h_pt_rew_weight_nolimit_(ctx.declare_event_output<float>("weight_pt_rew_nolimit")),
  h_pt_rew_weight_nolimit_down_(ctx.declare_event_output<float>("weight_pt_rew_down_nolimit")),
  apply_weight_(apply_weight),
  norm_factor_(norm_factor),
  ttgen_name_(ttgen_name){
  
  weight_name_ = weight_name;
  if(!weight_name_.empty())
    h_weight_= ctx.get_handle<float>(weight_name);
  version_ = ctx.get("dataset_version", "");
  boost::algorithm::to_lower(version_);
  if(!ttgen_name_.empty()){
    h_ttbargen_ = ctx.get_handle<TTbarGen>(ttgen_name);
  }
 
}


bool TopPtReweight::process(uhh2::Event& event){ 
  event.set(h_pt_rew_weight_, 1.f);
  event.set(h_pt_rew_weight_down_, 1.f);
  event.set(h_pt_rew_weight_nolimit_, 1.f);
  event.set(h_pt_rew_weight_nolimit_down_, 1.f);
  if (event.isRealData) return true; 
//  if (event.isRealData || (!boost::algorithm::contains(version_,"ttbar") && !boost::algorithm::contains(version_,"ttjets") && !boost::algorithm::starts_with(version_,"ttto")) ) {
//    return true;
//  }
  const TTbarGen& ttbargen = !ttgen_name_.empty() ? event.get(h_ttbargen_) : TTbarGen(*event.genparticles,false);
  
  float wgt = 1.;
  float wgt2 = 1.;
  if (ttbargen.DecayChannel() != TTbarGen::e_notfound) {
    float tpt1 = ttbargen.Top().v4().Pt();
    float tpt2 = ttbargen.Antitop().v4().Pt();
    wgt2 = sqrt(exp(a_+b_*tpt1)*exp(a_+b_*tpt2));
    tpt1 = std::min(tpt1, float(500.));
    tpt2 = std::min(tpt2, float(500.));
    wgt = sqrt(exp(a_+b_*tpt1)*exp(a_+b_*tpt2));
  }

  event.set(h_pt_rew_weight_,wgt); 
  event.set(h_pt_rew_weight_down_,2*wgt - 1);

  event.set(h_pt_rew_weight_nolimit_,wgt2);
  event.set(h_pt_rew_weight_nolimit_down_,2*wgt2 - 1);

//  if(!weight_name_.empty())
//    event.set(h_weight_, wgt);
//  if (apply_weight_) {
//    event.weight *= wgt*norm_factor_;
//  }
  return true;
}


TopPtReweightHist::TopPtReweightHist(uhh2::Context & ctx,
				     const string & dirname,
				     const string & weight_name):
  Hists(ctx, dirname),
  h_weight_(ctx.get_handle<float>(weight_name)),
  hist(book<TH1F>("ttbar_reweight_n_events",
		  ";bin 0: no weight, bin 1: with weight;events",
		  2, -.5, 1.5)) {}


void TopPtReweightHist::fill(const Event & event){
  if (event.is_valid(h_weight_)) {
    hist->Fill(0.);
    hist->Fill(1., event.get(h_weight_));
  }
}
